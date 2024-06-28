#include "database.h"
#include <stack>

Database::Database(const Config &configuration)
    : m_Configuration(configuration)
{
}

Database &Database::add(const File &fileToAdd)
{
  std::shared_ptr<File> file = fileToAdd.clone();
  auto checkIfInserted = m_Files.insert({file->getName(), file});

  if (checkIfInserted.second == false)
    std::cout << "ERROR: File \"" << file->getName() << "\" could not be added." << std::endl;

  return *this;
}

void Database::command(const std::string &command)
{
  CommandController evaluator;
  std::vector<std::string> slicedCommand;

  slicedCommand = evaluator.evaluateCommand(command);

  Relation foundRelation;
  std::vector<Relation> relationsArguments;
  std::stack<std::shared_ptr<Relation>> relations;
  std::stack<std::string> expressions;
  std::string tmp = "", tmpUpper = "", relationName = "";
  tmpUpper = slicedCommand.at(0);
  std::transform(tmpUpper.begin(), tmpUpper.end(), tmpUpper.begin(), [](unsigned char c)
                 { return std::toupper(c); });

  if (slicedCommand.size() && tmpUpper == "TRANSLATE")
  {
    slicedCommand.erase(slicedCommand.begin(), slicedCommand.begin() + 1);
    Translator translator(m_Configuration.getSubqueryPostfix());
    std::string translatedQuery = translator.translateToSQL(slicedCommand);
    std::cout << translatedQuery << std::endl;
    return;
  }

  tmpUpper = "";

  for (int i = slicedCommand.size() - 1; i >= 0; --i)
  {
    tmp = slicedCommand[i];

    if (tmp.size() >= 2 && tmp.front() == '\"' && tmp.back() == '\"')
    {
      expressions.push(tmp.substr(1, tmp.length() - 2));
    }
    else
    {
      tmpUpper = tmp;
      std::transform(tmpUpper.begin(), tmpUpper.end(), tmpUpper.begin(), [](unsigned char c)
                     { return std::toupper(c); });

      if (m_Operators.count(tmpUpper))
      {
        relationsArguments.erase(relationsArguments.begin(), relationsArguments.end());
        size_t relationCount = m_Operators.at(tmpUpper)->getRelationCount();

        for (size_t j = 0; j < relationCount; ++j)
        {
          if (!relations.empty())
          {
            relationsArguments.push_back(*relations.top());
            relations.pop();
          }
          else
          {
            throw std::runtime_error("ERROR: Missing parameters.");
          }
        }

        if (m_Operators.at(tmpUpper)->getExpressionCount() == 0)
        {
          relations.push(std::make_shared<Relation>(m_Operators.at(tmpUpper)->getResult(relationsArguments)));
        }
        else if (!expressions.empty())
        {
          relations.push(std::make_shared<Relation>((m_Operators.at(tmpUpper)->getResult(relationsArguments, expressions.top()))));
          expressions.pop();
        }
        else
        {
          throw std::runtime_error("ERROR: No expressions left.");
        }
      }
      else if (m_Commands.count(tmpUpper))
      {

        if (i != 0)
          throw std::runtime_error("ERROR: \"" + tmp + "\" has to be at the beginning.");

        if (tmpUpper == "PRINT")
        {
          if (relations.size() == 1)
          {
            relations.top()->print(m_Configuration.getSpacesBetweenColumns());
            relations.pop();
          }
          else
          {
            throw std::runtime_error("ERROR: \"PRINT\" has incorrect number of parameters.");
          }
        }
        else if (tmpUpper == "EXPORT")
        {
          if (relations.size() == 1 && expressions.size() == 1)
          {
            std::ifstream fin(expressions.top());

            if (fin.is_open())
            {
              std::cout << "The file \"" << expressions.top() << "\" already exists." << std::endl;
              std::cout << "Do you wish to overwrite it? (YES/NO)" << std::endl;
              std::cout << m_Configuration.getInputDelimeter();

              std::string answer;

              std::getline(std::cin, answer);
              std::transform(answer.begin(), answer.end(), answer.begin(), [](unsigned char c)
                             { return std::toupper(c); });
              if (answer == "YES")
                relations.top()->exportToFile(expressions.top());
              else if (answer == "NO")
                throw std::runtime_error("You did not allow overwriting the file.");
              else
                throw std::runtime_error("ERROR: \"" + answer + "\" not recognized.");
            }
            else
            {
              relations.top()->exportToFile(expressions.top());
            }
          }
          else
          {
            throw std::runtime_error("ERROR: \"EXPORT\" is missing a parameter.");
          }
          relations.pop();
          expressions.pop();
        }
        else if (tmpUpper == "IMPORT")
        {
          std::string outDatabaseName = expressions.top();
          expressions.pop();
          std::string inDatabaseName = expressions.top();
          expressions.pop();

          for (auto it = inDatabaseName.begin(); it != inDatabaseName.end(); ++it)
            if (isspace(*it))
              *it = '_';

          size_t posOfDot = outDatabaseName.find_last_of('.');
          std::string ending = outDatabaseName.substr(posOfDot + 1, outDatabaseName.size() - posOfDot);
          std::string endingUpper = outDatabaseName.substr(posOfDot + 1, outDatabaseName.size() - posOfDot);
          std::transform(endingUpper.begin(), endingUpper.end(), endingUpper.begin(), [](unsigned char c)
                         { return std::toupper(c); });

          if (m_Files.count(inDatabaseName) || m_Variables.count(inDatabaseName))
            throw std::runtime_error("ERROR: The variable name \"" + inDatabaseName + "\" is already taken.");

          std::shared_ptr<File> newFile;

          if (endingUpper == "CSV")
          {
            newFile = std::make_shared<CSVFile>(CSVFile(outDatabaseName));
          }
          else if (endingUpper == "TSV")
          {
            newFile = std::make_shared<TSVFile>(TSVFile(outDatabaseName));
          }
          newFile->setName(inDatabaseName);
          add(*newFile);
        }
      }
      else if (tmp == "=")
      {
        if (i != 1)
          throw std::runtime_error("ERROR: The \"=\" sign is not used correctly.");
        if (relations.size() != 1)
          throw std::runtime_error("ERROR: Incorrect number of parameters is being assigned to variable.");
        if (m_Files.count(slicedCommand.at(0)))
          m_Files.erase(slicedCommand.at(0));
        else if (m_Variables.count(slicedCommand.at(0)))
          m_Variables.erase(slicedCommand.at(0));

        m_Variables.insert({slicedCommand.at(0), relations.top()});
        relations.pop();

        break;
      }
      else
      {
        if (m_Files.count(tmp))
        {
          relations.push(std::make_shared<Relation>(m_Files.at(tmp)->turnIntoRelation()));
        }
        else if (m_Variables.count(tmp))
        {
          relations.push(m_Variables.at(tmp));
        }
        else
        {
          throw std::runtime_error("ERROR: \"" + tmp + "\" not found.");
        }
      }
    }
  }
  return;
}