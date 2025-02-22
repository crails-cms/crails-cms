#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"
#include <crails/utils/semantics.hpp>
#include <crails/cli/conventions.hpp>

class render_ProjectModelsUserGroupCpp : public Crails::Template
{
public:
  render_ProjectModelsUserGroupCpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    resource_name(Crails::cast< std::string >(vars, "resource_name")), 
    classname( Crails::naming_convention.classnames(resource_name)), 
    filename( Crails::naming_convention.filenames(resource_name))
  {}

  void render()
  {
ecpp_stream << "#include \"" << ( filename );
  ecpp_stream << ".hpp\"\n#include \"lib/odb/application-odb.hxx\"\n\nodb_instantiable_impl(" << ( classname );
  ecpp_stream << ")\n\nunsigned long " << ( classname );
  ecpp_stream << "::find_available_flag() const\n{\n  Crails::Odb::Connection database;\n  odb::result<UserGroup> groups;\n  unsigned long candidate_flag = 1;\n\n  database.rollback_on_destruction = false;\n  database.find<UserGroup>(groups, odb::query<UserGroup>(true) + \"ORDER BY\" + odb::query<UserGroup>::flag);\n  for (const UserGroup& group : groups)\n  {\n    if (group.get_flag() == candidate_flag)\n      candidate_flag *= 2;\n  }\n  return candidate_flag;\n}\n\nvoid " << ( classname );
  ecpp_stream << "::purge_flag() const\n{\n  Crails::Odb::Connection database;\n  odb::result<PermissionRule> rules;\n\n  database.find<PermissionRule>(rules);\n  for (PermissionRule rule : rules)\n  {\n    rule.purge_flag(get_flag());\n    database.save(rule);\n  }\n}\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
  std::string resource_name;
  std::string classname;
  std::string filename;
};

void render_project_models_user_group_cpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectModelsUserGroupCpp(renderer, target, vars).render();
}