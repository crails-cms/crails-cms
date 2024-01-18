#pragma once
#include <crails/cli/command.hpp>

class AddPlugin : public Crails::Command
{
public:
  std::string_view description() const override { return "Download and prepare a plugin from a github repository"; }
  void options_description(boost::program_options::options_description& desc) const override;
  int run() override;
private:
  std::string git_url() const;
};
