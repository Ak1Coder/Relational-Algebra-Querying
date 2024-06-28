#include "application.h"

Application::Application(const Config &configuration)
    : m_Configuration(configuration)
{
}

void Application::run() const
{
  std::string inputDelimeter = m_Configuration.getInputDelimeter();
  Database workingDatabase(m_Configuration);
  std::string inputLine = "";

  while (true)
  {
    std::cout << inputDelimeter;
    std::string line = "";

    if (!std::getline(std::cin, inputLine))
    {
      std::cout << std::endl;
      break;
    }

    if (upper(inputLine) == "EXIT")
    {
      break;
    }
    else if (inputLine.size() == 0)
    {
      continue;
    }

    try
    {
      workingDatabase.command(inputLine);
    }
    catch (const std::exception &exception)
    {
      std::cout << exception.what() << std::endl;
    }
  }
}

std::string Application::upper(const std::string &expression) const
{
  std::string result = expression;

  std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c)
                 { return std::toupper(c); });

  return result;
}
