#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"
#include <crails/cli/conventions.hpp>

class render_ProjectControllersAttachmentHpp : public Crails::Template
{
public:
  render_ProjectControllersAttachmentHpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    classname( Crails::naming_convention.classnames("AttachmentController")), 
    parent_class( Crails::naming_convention.classnames("ApplicationController")), 
    traits_class( Crails::naming_convention.classnames("AttachmentTraits")), 
    super_class( "Crails::Cms::AttachmentController<" + traits_class + ", " + parent_class + '>')
  {}

  void render()
  {
ecpp_stream << "#pragma once\n#include <crails/cms/controllers/attachments.hpp>\n#include \"application.hpp\"\n#include \"../models/attachment_traits.hpp\"\n\nclass " << ( classname );
  ecpp_stream << " : public " << ( super_class );
  ecpp_stream << "\n{\n  typedef " << ( super_class );
  ecpp_stream << " Super;\npublic:\n  " << ( classname );
  ecpp_stream << "(Crails::Context&);\n};\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
  std::string classname;
  std::string parent_class;
  std::string traits_class;
  std::string super_class;
};

void render_project_controllers_attachment_hpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectControllersAttachmentHpp(renderer, target, vars).render();
}