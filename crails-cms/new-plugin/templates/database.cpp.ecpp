#include <crails/odb/connection.hpp>

void install_plugin_database()
{
  Crails::Odb::Connection database;

  database.transaction.require("odb");
  // insert table creation here
  // Example:
  //
  //  database.execute(
  //    "CREATE TABLE \"Plugin_ClassName\" ();"
  //  );
  //
  database.commit();
}

void uninstall_plugin_database()
{
  Crails::Odb::Connection database;

  database.transaction.require("odb");
  // insert table droping here
  database.commit();
}
