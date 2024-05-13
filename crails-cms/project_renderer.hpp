#pragma once
#include <crails/renderer.hpp>
#include <fstream>
#include <crails/render_file.hpp>

class ProjectRenderer : public Crails::Renderer
{
public:
  ProjectRenderer();
  std::string_view get_name() const override { return "crails-cms/ProjectRenderer"; }
  const std::vector<std::string>& get_mimetypes() const override;
  bool can_render(const std::string& view) const override { return templates.find(view) != templates.end(); }
  void render_template(const std::string& view, Crails::RenderTarget& target, Crails::SharedVars& vars) const override
  {
    auto tpl = templates.find(view);
    tpl->second(*this, target, vars);
  }
};
