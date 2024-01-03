#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"
#include <crails/utils/semantics.hpp>
#include <crails/cli/conventions.hpp>

class render_ProjectModelsModelHpp : public Crails::Template
{
public:
  render_ProjectModelsModelHpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    resource_name(Crails::cast<std::string>(vars, "resource_name")), 
    include_path(Crails::cast<std::string>(vars, "include_path",  Crails::underscore(resource_name))), 
    classname( Crails::naming_convention.classnames(resource_name))
  {}

  void render()
  {
ecpp_stream << "#pragma once\n#include <crails/cms/models/" << ( include_path );
  ecpp_stream << ".hpp>\n\n#pragma db object\nclass " << ( classname );
  ecpp_stream << " : public Crails::Cms::" << ( Crails::camelize(resource_name) );
  ecpp_stream << "\n{\n  odb_instantiable()\npublic:\n  #pragma db view object(" << ( classname );
  ecpp_stream << ")\n  struct Count\n  {\n    #pragma db column(\"count(\" + " << ( classname );
  ecpp_stream << "::id + \")\")\n    size_t value;\n  };\n};\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
  std::string resource_name;
  std::string include_path;
  std::string classname;
};

void render_project_models_model_hpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectModelsModelHpp(renderer, target, vars).render();
}