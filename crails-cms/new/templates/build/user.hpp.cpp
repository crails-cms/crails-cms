#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"
#include <crails/utils/semantics.hpp>
#include <crails/cli/conventions.hpp>

class render_ProjectModelsUserHpp : public Crails::Template
{
public:
  render_ProjectModelsUserHpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    resource_name(Crails::cast<std::string>(vars, "resource_name")), 
    classname( Crails::naming_convention.classnames(resource_name)), 
    group_classname( Crails::naming_convention.classnames("user_group"))
  {}

  void render()
  {
ecpp_stream << "#pragma once\n#include <crails/odb/helpers.hpp>\n#include <crails/cms/models/" << ( Crails::underscore(resource_name) );
  ecpp_stream << ".hpp>\n#include \"user_group.hpp\"\n\n#pragma db object\nclass " << ( classname );
  ecpp_stream << " : public Crails::Cms::" << ( Crails::camelize(resource_name) );
  ecpp_stream << "\n{\n  odb_instantiable()\npublic:\n  #pragma db view object(" << ( classname );
  ecpp_stream << ")\n  struct Count\n  {\n    #pragma db column(\"count(\" + " << ( classname );
  ecpp_stream << "::id + \")\")\n    size_t value;\n  };\n\n  " << ( classname );
  ecpp_stream << "() : permissions(groups)\n  {\n  }\n\n  unsigned long get_group_flag() const override { return permissions.get_group_flag(); }\n  Crails::Cms::UserPermissions<" << ( group_classname );
  ecpp_stream << "> get_permissions() { return permissions; }\n  std::vector<Crails::Odb::id_type> get_group_ids() const override { return collect_ids_from(groups); }\n\nprivate:\n  std::vector<std::shared_ptr<" << ( group_classname );
  ecpp_stream << ">> groups;\n  #pragma db transient\n  Crails::Cms::UserPermissions<" << ( group_classname );
  ecpp_stream << "> permissions;\n};\n";
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

void render_project_models_user_hpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectModelsUserHpp(renderer, target, vars).render();
}