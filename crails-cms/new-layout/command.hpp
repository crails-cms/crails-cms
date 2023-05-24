#pragma once
#include <crails/cli/command.hpp>
#include "../file_renderer.hpp"

class NewLayout : public Crails::Command
{
public:
  std::string_view description() const override { return "Creates a new layout plugin."; }
  void options_description(boost::program_options::options_description& desc) const override;
  int run() override;
private:
  void load_options();

  bool generate_file(const std::string& filepath) { return renderer.generate_file("layouts/" + filepath, filepath); }

  FileRenderer renderer;
  std::string project_name, folder_target;
};

