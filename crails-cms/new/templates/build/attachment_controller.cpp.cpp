#include <crails/template_stream.hpp>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"
#include <crails/cli/conventions.hpp>

class render_ProjectControllersAttachmentCpp : public Crails::Template
{
public:
  render_ProjectControllersAttachmentCpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    classname( Crails::naming_convention.classnames("AttachmentController")), 
    parent_class( Crails::naming_convention.classnames("ApplicationController"))
  {}

  void render()
  {
    ecpp_stream.reserve(452);
    // BEGIN TEMPLATE BODY
ecpp_stream << "#include \"attachment.hpp\"\n#include \"app/autogen/odb/application-odb.hpp\"\n" << ( classname );
  ecpp_stream << "::" << ( classname );
  ecpp_stream << "(Crails::Context& context) : Super(context)\n{\n}\n";
    // END TEMPLATE BODY
    std::string _out_buffer = std::move(ecpp_stream).extract();
    this->target.set_body(this->apply_post_render_filters(std::move(_out_buffer)));
  }
private:
  Crails::TemplateStream ecpp_stream;
  std::string classname;
  std::string parent_class;
};

void render_project_controllers_attachment_cpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectControllersAttachmentCpp(renderer, target, vars).render();
}