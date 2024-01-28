#!/bin/bash -ex
ECPP=ecpp
PROJECT_TPL=crails-cms/new/templates
RENDERERS_TPL=crails-cms/templates
SCAFFOLDS_TPL=crails-cms/scaffolds/templates
##
## AppTemplate
##
mkdir -p $PROJECT_TPL/build
$ECPP \
 -n ProjectAppMain \
 -i $PROJECT_TPL/main.cpp.ecpp \
 >  $PROJECT_TPL/build/main.cpp
$ECPP \
 -n ProjectAppRoutesCpp \
 -i $PROJECT_TPL/routes.cpp.ecpp \
 >  $PROJECT_TPL/build/routes.cpp
$ECPP \
 -n ProjectConfigRenderers \
 -i $PROJECT_TPL/renderers.cpp.ecpp \
 >  $PROJECT_TPL/build/renderers.cpp
$ECPP \
 -n ProjectConfigRequestPipe \
 -i $PROJECT_TPL/request_pipe.cpp.ecpp \
 >  $PROJECT_TPL/build/request_pipe.cpp
$ECPP \
 -n ProjectConfigCmsLayoutsHpp \
 -i $PROJECT_TPL/config/cms_layouts.hpp.ecpp \
 >  $PROJECT_TPL/build/cms_layouts.hpp.cpp
$ECPP \
 -n ProjectConfigCmsLayoutsCpp \
 -i $PROJECT_TPL/config/cms_layouts.cpp.ecpp \
 >  $PROJECT_TPL/build/cms_layouts.cpp
$ECPP \
 -n ProjectConfigCmsMenusHpp \
 -i $PROJECT_TPL/config/cms_menus.hpp.ecpp \
 >  $PROJECT_TPL/build/cms_menus.hpp.cpp
$ECPP \
 -n ProjectConfigCmsPluginsHpp \
 -i $PROJECT_TPL/config/cms_plugins.hpp.ecpp \
 >  $PROJECT_TPL/build/cms_plugins.hpp.cpp
$ECPP \
 -n ProjectConfigCmsPluginsCpp \
 -i $PROJECT_TPL/config/cms_plugins.cpp.ecpp \
 >  $PROJECT_TPL/build/cms_plugins.cpp.cpp
$ECPP \
 -n ProjectModelsTraits \
 -i $PROJECT_TPL/models/traits.hpp.ecpp \
 >  $PROJECT_TPL/build/traits.hpp.cpp
$ECPP \
 -n ProjectModelsModelHpp \
 -i $PROJECT_TPL/models/model.hpp.ecpp \
 >  $PROJECT_TPL/build/main.hpp.cpp
$ECPP \
 -n ProjectModelsModelCpp \
 -i $PROJECT_TPL/models/model.cpp.ecpp \
 >  $PROJECT_TPL/build/model.cpp
$ECPP \
 -n ProjectModelsResourceTraitsHpp \
 -i $PROJECT_TPL/models/resource_traits.hpp.ecpp \
 >  $PROJECT_TPL/build/resource_traits.hpp.cpp
$ECPP \
 -n ProjectModelsTagQueryHpp \
 -i $PROJECT_TPL/models/tag_query.hpp.ecpp \
 >  $PROJECT_TPL/build/tag_query.hpp.cpp
$ECPP \
 -n ProjectModelsUserHpp \
 -i $PROJECT_TPL/models/user.hpp.ecpp \
 >  $PROJECT_TPL/build/user.hpp.cpp
$ECPP \
 -n ProjectModelsUserGroupHpp \
 -i $PROJECT_TPL/models/user_group.hpp.ecpp \
 >  $PROJECT_TPL/build/user_group.hpp.cpp
$ECPP \
 -n ProjectModelsUserGroupCpp \
 -i $PROJECT_TPL/models/user_group.cpp.ecpp \
 >  $PROJECT_TPL/build/user_group.cpp.cpp
$ECPP \
 -n ProjectModelsPermissionRuleHpp \
 -i $PROJECT_TPL/models/permission_rule.hpp.ecpp \
 >  $PROJECT_TPL/build/permission_rule.hpp.cpp
$ECPP \
 -n ProjectModelsPermissionRuleCpp \
 -i $PROJECT_TPL/models/permission_rule.cpp.ecpp \
 >  $PROJECT_TPL/build/permission_rule.cpp.cpp
$ECPP \
 -n ProjectModelsHomepageHpp \
 -i $PROJECT_TPL/models/homepage.hpp.ecpp \
 >  $PROJECT_TPL/build/homepage.cpp
$ECPP \
 -n ProjectControllersApplicationHpp \
 -i $PROJECT_TPL/controllers/application.hpp.ecpp \
 >  $PROJECT_TPL/build/application_controller.hpp.cpp
$ECPP \
 -n ProjectControllersApplicationCpp \
 -i $PROJECT_TPL/controllers/application.cpp.ecpp \
 >  $PROJECT_TPL/build/application_controller.cpp.cpp
$ECPP \
 -n ProjectControllersSigninHpp \
 -i $PROJECT_TPL/controllers/signin.hpp.ecpp \
 >  $PROJECT_TPL/build/signin_controller.hpp.cpp
$ECPP \
 -n ProjectControllersSigninCpp \
 -i $PROJECT_TPL/controllers/signin.cpp.ecpp \
 >  $PROJECT_TPL/build/signin_controller.cpp.cpp
$ECPP \
 -n ProjectControllersHomeHpp \
 -i $PROJECT_TPL/controllers/home.hpp.ecpp \
 >  $PROJECT_TPL/build/home_controller.hpp.cpp
$ECPP \
 -n ProjectControllersHomeCpp \
 -i $PROJECT_TPL/controllers/home.cpp.ecpp \
 >  $PROJECT_TPL/build/home_controller.cpp.cpp
$ECPP \
 -n ProjectControllersResourceHpp \
 -i $PROJECT_TPL/controllers/resource.hpp.ecpp \
 >  $PROJECT_TPL/build/resource_controller.hpp.cpp
$ECPP \
 -n ProjectControllersAdminApplicationHpp \
 -i $PROJECT_TPL/controllers/admin/application.hpp.ecpp \
 >  $PROJECT_TPL/build/admin_controller.hpp.cpp
$ECPP \
 -n ProjectControllersAdminResourceHpp \
 -i $PROJECT_TPL/controllers/admin/resource.hpp.ecpp \
 >  $PROJECT_TPL/build/admin_resource_controller.hpp.cpp
$ECPP \
 -n ProjectControllersAdminSettingsHpp \
 -i $PROJECT_TPL/controllers/admin/settings.hpp.ecpp \
 >  $PROJECT_TPL/build/admin_settings_controller.hpp.cpp
$ECPP \
 -n ProjectControllersAdminOpengraphHpp \
 -i $PROJECT_TPL/controllers/admin/opengraph.hpp.ecpp \
 >  $PROJECT_TPL/build/admin_opengraph_controller.hpp.cpp

##
## Plugin template
##
PLUGIN_TPL=crails-cms/new-plugin/templates
$ECPP \
 -n PluginCrailsfile \
 -i $PLUGIN_TPL/crailsfile.ecpp \
 >  $PLUGIN_TPL/build/crailsfile.cpp
$ECPP \
 -n PluginCmakelistsTxt \
 -i $PLUGIN_TPL/CMakeLists.txt.ecpp \
 >  $PLUGIN_TPL/build/CMakeLists.txt.cpp
$ECPP \
 -n PluginPrebuildSh \
 -i $PLUGIN_TPL/prebuild.sh.ecpp \
 >  $PLUGIN_TPL/build/prebuild.sh.cpp
$ECPP \
 -n PluginPackageJson \
 -i $PLUGIN_TPL/package.json.ecpp \
 >  $PLUGIN_TPL/build/package.json.cpp
$ECPP \
 -n PluginAppMainCpp \
 -i $PLUGIN_TPL/main.cpp.ecpp \
 >  $PLUGIN_TPL/build/main.cpp
$ECPP \
 -n PluginAppRoutesCpp \
 -i $PLUGIN_TPL/routes.cpp.ecpp \
 >  $PLUGIN_TPL/build/routes.cpp
$ECPP \
 -n PluginAppRenderersCpp \
 -i $PLUGIN_TPL/renderers.cpp.ecpp \
 >  $PLUGIN_TPL/build/renderers.cpp
$ECPP \
 -n PluginAppDatabaseCpp \
 -i $PLUGIN_TPL/database.cpp.ecpp \
 >  $PLUGIN_TPL/build/database.cpp
$ECPP \
 -n  PluginWebpackConfigJs \
 -i $PLUGIN_TPL/webpack.config.js.ecpp \
 >  $PLUGIN_TPL/build/webpack.config.js.cpp

##
## Layout plugin template
##
PLUGIN_TPL=crails-cms/new-layout/templates
$ECPP \
 -n LayoutPluginCrailsfile \
 -i $PLUGIN_TPL/crailsfile.ecpp \
 >  $PLUGIN_TPL/build/crailsfile.cpp
$ECPP \
 -n LayoutPluginCmakelistsTxt \
 -i $PLUGIN_TPL/CMakeLists.txt.ecpp \
 >  $PLUGIN_TPL/build/CMakeLists.txt.cpp
$ECPP \
 -n LayoutPluginPackageJson \
 -i $PLUGIN_TPL/package.json.ecpp \
 >  $PLUGIN_TPL/build/package.json.cpp
$ECPP \
 -n LayoutPluginWebpackConfigJs \
 -i $PLUGIN_TPL/webpack.config.js.ecpp \
 >  $PLUGIN_TPL/build/webpack.config.js.cpp
$ECPP \
 -n LayoutPluginMainCpp \
 -i $PLUGIN_TPL/main.cpp.ecpp \
 >  $PLUGIN_TPL/build/main.cpp.cpp
$ECPP \
 -n LayoutPluginPrebuildSh \
 -i $PLUGIN_TPL/prebuild.sh.ecpp \
 >  $PLUGIN_TPL/build/prebuild.sh.cpp
$ECPP \
 -n LayoutPluginStyleHpp \
 -i $PLUGIN_TPL/style.hpp.ecpp \
 >  $PLUGIN_TPL/build/style.hpp.cpp
$ECPP \
 -n LayoutPluginLayoutHpp \
 -i $PLUGIN_TPL/layout.hpp.ecpp \
 >  $PLUGIN_TPL/build/layout.hpp.cpp
$ECPP \
 -n LayoutPluginLayoutCpp \
 -i $PLUGIN_TPL/layout.cpp.ecpp \
 >  $PLUGIN_TPL/build/layout.cpp.cpp
$ECPP \
 -n LayoutPluginLayoutHtml \
 -i $PLUGIN_TPL/layout.html.ecpp \
 >  $PLUGIN_TPL/build/layout.html.cpp
$ECPP \
 -n LayoutPluginLayoutScss \
 -i $PLUGIN_TPL/layout.scss.ecpp \
 >  $PLUGIN_TPL/build/layout.scss.cpp
$ECPP \
 -n LayoutPluginAdminScss \
 -i $PLUGIN_TPL/admin.scss.ecpp \
 >  $PLUGIN_TPL/build/admin.scss.cpp
$ECPP \
  -n LayoutPluginFontsScss \
  -i $PLUGIN_TPL/fonts.scss.ecpp \
  >  $PLUGIN_TPL/build/fonts.scss.cpp
$ECPP \
 -n LayoutPluginThemeScss \
 -i $PLUGIN_TPL/theme.scss.ecpp \
 >  $PLUGIN_TPL/build/theme.scss.cpp
$ECPP \
 -n LayoutPluginEditorJs \
 -i $PLUGIN_TPL/editor.js.ecpp \
 >  $PLUGIN_TPL/build/editor.js.cpp
$ECPP \
 -n LayoutPluginIndexJs \
 -i $PLUGIN_TPL/index.js.ecpp \
 >  $PLUGIN_TPL/build/index.js.cpp
