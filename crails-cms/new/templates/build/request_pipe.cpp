#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"

class render_ProjectConfigRequestPipe : public Crails::Template
{
public:
  render_ProjectConfigRequestPipe(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars)
  {}

  void render()
  {
ecpp_stream << "#include <crails/request_parsers/url_parser.hpp>\n#include <crails/request_parsers/form_parser.hpp>\n#include <crails/request_parsers/multipart_parser.hpp>\n#include <crails/request_handlers/file.hpp>\n#include <crails/request_handlers/action.hpp>\n#include <crails/request_parser.hpp>\n#include <crails/cms/views/layout.hpp>\n#include <crails/cms/lib/assets.hpp>\n#include \"server.hpp\"\n\nusing namespace Crails;\nusing namespace std;\n\nstatic CrailsCmsAssets cms_assets;\n\nvoid ApplicationServer::initialize_request_pipe()\n{\n  const auto& layouts = Crails::Cms::Layouts::singleton::require();\n\n  add_request_parser(new RequestUrlParser);\n  add_request_parser(new RequestFormParser);\n  add_request_parser(new RequestMultipartParser);\n  add_request_handler(new Crails::BuiltinAssetsHandler(cms_assets));\n  layouts.load_assets(\n    bind(&ApplicationServer::add_request_handler, this, placeholders::_1)\n  );\n  add_request_handler(new FileRequestHandler);\n  add_request_handler(new ActionRequestHandler);\n}\n";
    this->target.set_body(ecpp_stream.str());
  }
private:
  std::stringstream ecpp_stream;
};

void render_project_config_request_pipe(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectConfigRequestPipe(renderer, target, vars).render();
}