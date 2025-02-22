#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"
#include <crails/utils/semantics.hpp>
#include <crails/cli/conventions.hpp>

class render_ProjectModelsUserGroupHpp : public Crails::Template
{
public:
  render_ProjectModelsUserGroupHpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    resource_name(Crails::cast< std::string >(vars, "resource_name")), 
    classname( Crails::naming_convention.classnames(resource_name))
  {}

  void render()
  {
ecpp_stream << "#pragma once\n#include <crails/cms/models/user_group.hpp>\n\n#pragma db object\nclass " << ( classname );
  ecpp_stream << " : public Crails::Cms::UserGroup\n{\n  odb_instantiable()\npublic:\n  #pragma db view object(" << ( classname );
  ecpp_stream << ")\n  struct Count\n  {\n    #pragma db column(\"count(\" + " << ( classname );
  ecpp_stream << "::id + \")\")\n    size_t value;\n  };\n\nprivate:\n  unsigned long find_available_flag() const override;\n  void purge_flag() const override;\n};\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
  std::string resource_name;
  std::string classname;
};

void render_project_models_user_group_hpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectModelsUserGroupHpp(renderer, target, vars).render();
}