/* RowSetMetaData.java 
   Copyright (C) 2002 Free Software Foundation, Inc.

This file is part of GNU Classpath.

GNU Classpath is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.
 
GNU Classpath is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Classpath; see the file COPYING.  If not, write to the
Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
02110-1301 USA.

Linking this library statically or dynamically with other modules is
making a combined work based on this library.  Thus, the terms and
conditions of the GNU General Public License cover the whole
combination.

As a special exception, the copyright holders of this library give you
permission to link this library with independent modules to produce an
executable, regardless of the license terms of these independent
modules, and to copy and distribute the resulting executable under
terms of your choice, provided that you also meet, for each linked
independent module, the terms and conditions of the license of that
module.  An independent module is a module which is not derived from
or based on this library.  If you modify this library, you may extend
this exception to your version of the library, but you are not
obligated to do so.  If you do not wish to do so, delete this
exception statement from your version. */


package javax.sql;

import java.sql.ResultSetMetaData;
import java.sql.SQLException;

/**
 * @since 1.4
 */
public interface RowSetMetaData extends ResultSetMetaData 
{
  void setColumnCount(int columnCount) throws SQLException;

  void setAutoIncrement(int columnIndex, boolean property)
    throws SQLException;

  void setCaseSensitive(int columnIndex, boolean property)
    throws SQLException;

  void setSearchable(int columnIndex, boolean property)
    throws SQLException;

  void setCurrency(int columnIndex, boolean property)
    throws SQLException;

  void setNullable(int columnIndex, int property) throws SQLException;

  void setSigned(int columnIndex, boolean property)
    throws SQLException;

  void setColumnDisplaySize(int columnIndex, int size)
    throws SQLException;

  void setColumnLabel(int columnIndex, String label)
    throws SQLException;

  void setColumnName(int columnIndex, String columnName)
    throws SQLException;

  void setSchemaName(int columnIndex, String schemaName)
    throws SQLException;

  void setPrecision(int columnIndex, int precision)
    throws SQLException;

  void setScale(int columnIndex, int scale) throws SQLException;

  void setTableName(int columnIndex, String tableName)
    throws SQLException;

  void setCatalogName(int columnIndex, String catalogName)
    throws SQLException;

  void setColumnType(int columnIndex, int SQLType) throws SQLException;

  void setColumnTypeName(int columnIndex, String typeName)
    throws SQLException;
}
