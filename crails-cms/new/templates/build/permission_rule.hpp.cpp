#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"
#include <crails/utils/semantics.hpp>
#include <crails/cli/conventions.hpp>

class render_ProjectModelsPermissionRuleHpp : public Crails::Template
{
public:
  render_ProjectModelsPermissionRuleHpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    resource_name(Crails::cast< std::string >(vars, "resource_name")), 
    classname( Crails::naming_convention.classnames(resource_name)), 
    group_classname( Crails::naming_convention.classnames("user_group"))
  {}

  void render()
  {
ecpp_stream << "#pragma once\n#include <crails/cms/models/permission_rule.hpp>\n#include \"" << ( Crails::naming_convention.filenames("user_group") );
  ecpp_stream << ".hpp\"\n\n#pragma db object\nclass " << ( classname );
  ecpp_stream << " : public Crails::Cms::PermissionRule\n{\n  odb_instantiable()\npublic:\n  #pragma db view object(" << ( classname );
  ecpp_stream << ")\n  struct Count\n  {\n    #pragma db column(\"count(\" + " << ( classname );
  ecpp_stream << "::id + \")\")\n    size_t value;\n  };\n\n  typedef void (" << ( classname  );
  ecpp_stream << "::*PermissionSetter)(const std::vector<" << ( group_classname );
  ecpp_stream << ">&);\n\n  void edit(Data);\n\nprivate:\n  void set_groups(Data, PermissionSetter);\n};\n";
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

void render_project_models_permission_rule_hpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectModelsPermissionRuleHpp(renderer, target, vars).render();
}