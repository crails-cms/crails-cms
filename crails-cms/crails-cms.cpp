#include <iostream>
#include <crails/cli/command_index.hpp>
#include "new/command.hpp"
#include "new-plugin/command.hpp"
#include "new-layout/command.hpp"

using namespace Crails;
using namespace std;

class Index : public CommandIndex
{
public:
  Index()
  {
    add_command("new", []() { return make_shared<New>(); });
    add_command("new-plugin", []() { return make_shared<NewPlugin>(); });
    add_command("new-layout", []() { return make_shared<NewLayout>(); });
  }
};

int main (int argc, const char* argv[])
{
  SingletonInstantiator<Renderers> renderer;
  Index index;

  if (index.initialize(argc, argv))
    return index.run();
  return -1;
}
