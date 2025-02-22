#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"
#include <crails/utils/semantics.hpp>
#include <crails/cli/conventions.hpp>

class render_ProjectModelsModelCpp : public Crails::Template
{
public:
  render_ProjectModelsModelCpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    resource_name(Crails::cast< std::string >(vars, "resource_name")), 
    classname( Crails::naming_convention.classnames(resource_name)), 
    filename( Crails::naming_convention.filenames(resource_name))
  {}

  void render()
  {
ecpp_stream << "#include  \"" << ( filename );
  ecpp_stream << ".hpp\"\n#include \"app/autogen/odb/application-odb.hpp\"\n\nodb_instantiable_impl(" << ( classname );
  ecpp_stream << ")\n";
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

void render_project_models_model_cpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectModelsModelCpp(renderer, target, vars).render();
}