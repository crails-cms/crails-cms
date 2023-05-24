#pragma once
#include <crails/cli/command.hpp>
#include "../file_renderer.hpp"

class New : public Crails::Command
{
public:
  std::string_view description() const override { return "Creates a new CMS application."; }
  void options_description(boost::program_options::options_description& desc) const override;
  int run() override;
private:
  void load_options();
  bool create_crails_application();
  bool add_crails_plugins();
  void generate_controllers();
  void generate_admin_controllers();
  void generate_models();
  void generate_model(const std::string& resource_name);
  void generate_user_group_model();
  void generate_permission_rule_model();
  bool generate_file(std::string_view filepath) { return renderer.generate_file(filepath, filepath); }

  FileRenderer renderer;
  std::string project_name, folder_target;
  std::string database_type;
};
