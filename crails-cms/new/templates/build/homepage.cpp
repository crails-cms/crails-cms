#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"
#include <crails/cli/conventions.hpp>

class render_ProjectModelsHomepageHpp : public Crails::Template
{
public:
  render_ProjectModelsHomepageHpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    settings_classname( Crails::naming_convention.classnames("settings")), 
    page_classname( Crails::naming_convention.classnames("page"))
  {}

  void render()
  {
ecpp_stream << "#pragma once\n#include \"" << ( Crails::naming_convention.filenames("settings") );
  ecpp_stream << ".hpp\"\n#include \"" << ( Crails::naming_convention.filenames("page") );
  ecpp_stream << ".hpp\"\n\n#pragma db view object(" << ( settings_classname );
  ecpp_stream << ") \\\n  object(" << ( page_classname );
  ecpp_stream << " = page left: " << ( settings_classname );
  ecpp_stream << "::homepage_id == page::id)\nstruct " << ( Crails::naming_convention.classnames("SettingsHomepageQuery") );
  ecpp_stream << "\n{\n  std::string get_database_name() { return ::" << ( settings_classname );
  ecpp_stream << "().get_database_name(); }\n  Crails::Odb::id_type get_id() const { return settings ? settings->get_id() : ODB_NULL_ID; }\n\n  std::shared_ptr<" << ( settings_classname );
  ecpp_stream << "> settings;\n  std::shared_ptr<" << ( page_classname );
  ecpp_stream << "> page;\n\n  #pragma db view object(" << ( settings_classname );
  ecpp_stream << ") object(" << ( page_classname );
  ecpp_stream << " inner: " << ( settings_classname );
  ecpp_stream << "::homepage_id == " << ( page_classname );
  ecpp_stream << "::id)\n  struct Count\n  {\n    #pragma db column(\"count(\" + " << ( settings_classname );
  ecpp_stream << "::id + \")\")\n    size_t value;\n  };\n};\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
  std::string settings_classname;
  std::string page_classname;
};

void render_project_models_homepage_hpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectModelsHomepageHpp(renderer, target, vars).render();
}