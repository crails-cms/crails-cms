#include <crails/cli/with_path.hpp>
#include <crails/cli/process.hpp>
#include <iostream>
#include "command.hpp"

using namespace std;

static string std_plugin_url(const std::string& plugin_name)
{
  static const string std_plugins_url = "https://github.com/crails-cms";
  return std_plugins_url + '/' + plugin_name + "-plugin";
}

void AddPlugin::options_description(boost::program_options::options_description& desc) const
{
  desc.add_options()
    ("name,n", boost::program_options::value<string>(), "plugin name")
    ("git,g", boost::program_options::value<string>(), "git repository url");
}

int AddPlugin::run()
{
  if (options.count("name"))
  {
    Crails::WithPath plugins_path("plugins");

    if (Crails::run_command("git clone \"" + git_url() + '"'))
    {
      // TODO do some stuff about the plugin ?
      return 0;
    }
    else
      cerr << "could not clone repository " << git_url() << endl;
  }
  else
    cerr << "no plugin name was provided" << endl;
  return -1;
}

string AddPlugin::git_url() const
{
  if (options.count("git"))
    return options["git"].as<string>();
  return std_plugin_url(options["name"].as<string>());
}
