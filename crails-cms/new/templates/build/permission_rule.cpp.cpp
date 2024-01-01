#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"
#include <crails/utils/semantics.hpp>
#include <crails/cli/conventions.hpp>

class render_ProjectModelsPermissionRuleCpp : public Crails::Template
{
public:
  render_ProjectModelsPermissionRuleCpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    resource_name(Crails::cast<std::string>(vars, "resource_name")), 
    classname( Crails::naming_convention.classnames(resource_name)), 
    group_classname( Crails::naming_convention.classnames("user_group"))
  {}

  void render()
  {
ecpp_stream << "#include \"" << ( Crails::naming_convention.filenames("permission_rule") );
  ecpp_stream << ".hpp\"\n#include \"lib/odb/application-odb.hxx\"\n#include <crails/odb/any.hpp>\n\nodb_instantiable_impl(PermissionRule)\n\nusing namespace Crails;\nusing namespace std;\n\nstatic const map<string, PermissionRule::PermissionSetter> permission_setters = {\n  {\"read_groups\",    &PermissionRule::set_read_groups<vector<" << ( group_classname );
  ecpp_stream << ">>},\n  {\"write_groups\",   &PermissionRule::set_write_groups<vector<" << ( group_classname );
  ecpp_stream << ">>},\n  {\"destroy_groups\", &PermissionRule::set_destroy_groups<vector<" << ( group_classname );
  ecpp_stream << ">>}\n};\n\nstatic odb::query<" << ( group_classname );
  ecpp_stream << "> make_group_query(Data ids)\n{\n  return odb::query<" << ( group_classname );
  ecpp_stream << ">::id + \"=\" + Odb::any(ids.to_vector<Crails::Odb::id_type>());\n}\n\nvoid " << ( classname );
  ecpp_stream << "::set_groups(Data ids, PermissionSetter setter)\n{\n  Crails::Odb::Connection database;\n  odb::result<" << ( group_classname );
  ecpp_stream << "> groups;\n\n  database.rollback_on_destruction = false;\n  database.find<" << ( group_classname );
  ecpp_stream << ">(groups, make_group_query(ids));\n  (this->*setter)(Odb::to_vector<" << ( group_classname );
  ecpp_stream << ">(groups));\n}\n\nvoid " << ( classname );
  ecpp_stream << "::edit(Data data)\n{\n  for (auto it = permission_setters.begin() ; it != permission_setters.end() ; ++it)\n  {\n    Data group_ids = data[it->first];\n\n    if (group_ids.exists())\n      set_groups(group_ids, it->second);\n  }\n}\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
  std::string resource_name;
  std::string classname;
  std::string group_classname;
};

void render_project_models_permission_rule_cpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectModelsPermissionRuleCpp(renderer, target, vars).render();
}