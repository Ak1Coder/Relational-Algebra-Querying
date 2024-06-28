#include <cstdlib>
#include "application.h"

int main()
{
  try
  {
    Config configuration("examples/config.txt");
    Application app(configuration);
    app.run();
  }
  catch (const std::exception &exception)
  {
    std::cout << exception.what() << std::endl;
  }
  return EXIT_SUCCESS;
}