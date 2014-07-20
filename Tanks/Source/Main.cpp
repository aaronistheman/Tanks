#include <Tanks/Application.hpp>

#include <stdexcept>
#include <iostream>

int main()
{
  try
	{
    throw std::exception("hi");
		Application app;
		app.run();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
}
