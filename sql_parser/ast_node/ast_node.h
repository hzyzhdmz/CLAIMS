/*
 * Copyright [2012-2015] DaSE@ECNU
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ./sql_parser/ast_node/ast_node.h
 *  Created on: May 21, 2015 4:10:35 PM
 *      Author: fzh
 *       Email: fzhedu@gmail.com
 *
 */

#ifndef AST_NODE_H_  // NOLINT
#define AST_NODE_H_
#include <iosfwd>
#include <vector>
#include <utility>
#include <set>
#include <map>
#include <string>
using std::pair;
using std::set;
using std::map;
using std::multimap;
using std::string;

enum AstNodeType {
  AST_NODE,
  AST_STMT_LIST,

  AST_SELECT_LIST,
  AST_SELECT_EXPR,
  AST_FROM_LIST,
  AST_TABLE,
  AST_SUBQUERY,
  AST_JOIN_CONDITION,
  AST_JOIN,
  AST_WHERE_CLAUSE,
  AST_GROUPBY_LIST,
  AST_GROUPBY_CLAUSE,
  AST_ORDERBY_LIST,
  AST_ORDERBY_CLAUSE,
  AST_HAVING_CLAUSE,
  AST_LIMIT_CLAUSE,
  AST_SELECT_INTO_CLAUSE,
  AST_COLUMN,
  AST_SELECT_STMT,
  AST_EXPR_LIST,
  AST_EXPR_CONST,
  AST_EXPR_UNARY,
  AST_EXPR_CAL_BINARY,
  AST_EXPR_CMP_BINARY,
  AST_EXPR_FUNC,

  AST_CREATE_DATABASE,
  AST_CREATE_SCHEMA,
  AST_CREATE_TABLE_LIST,
  AST_CREATE_TABLE_LIST_SEL,
  AST_CREATE_TABLE_SEL,
  AST_CREATE_COL_LIST,
  AST_CREATE_DEF_NAME,
  AST_CREATE_DEF_PR_KEY,
  AST_CREATE_DEF_KEY,
  AST_CREATE_DEF_INDEX,
  AST_CREATE_SEL,
  AST_CREATE_DEF_FTEXT_INDEX,
  AST_CREATE_DEF_FTEXT_KEY,
  AST_CREATE_INDEX,
  AST_LOAD_TABLE,
  AST_INDEX_COL,
  AST_INDEX_COL_LIST,
  AST_COLUMN_ATTS,
  AST_DATA_TYPE,
  AST_ENUM,
  AST_ENUM_LIST,
  AST_OPT_LENGTH,
  AST_OPT_CSC,
  AST_CREATE_PROJECTION,
  AST_CREATE_PROJECTION_NUM,
  AST_DROP_INDEX,
  AST_DROP_DB,
  AST_DROP_SCHEMA,
  AST_DROP_TABLE,
  AST_DROP_TABLE_LIST,
  AST_INSERT_STMT,
  AST_INSERT_VALUE_LIST,
  AST_INSERT_VALUE,
  AST_INSERT_ASSIGN_LIST,

  AST_INTNUM,
  AST_APPROXNUM,
  AST_STRINGVAL,
  AST_BOOL,
};
const int TAB_SIZE = 4;
/**
 * @brief The basic data structure of other AST nodes.
 */
class AstNode {
 public:
  /**
   * @brief The Semantic analysis middle scheme context.
   * @details SemanticContext mainly includes a multimap used for storing middle
   * scheme and a set for storing table name.
   * IsTableExist(string table_name) is used for judging whether table_name is
   * in the set<string>table_name_.
   * IsColumnExist(string column) is used for  judging whether column is in the
   * column_to_table_.
   */
  class SemanticContext {
   public:
    multimap<string, string> column_to_table_;
    set<string> table_name_;
    bool IsTableExist(string table_name) {}
    bool IsColumnExist(string column) {}
  };
  explicit AstNode(AstNodeType ast_node_type);
  virtual ~AstNode();
  virtual void Print(int level = 0) const;
  virtual int SemanticAnalysis();
  AstNodeType ast_node_type();
  AstNodeType ast_node_type_;
};
struct ParseResult {
  void* yyscan_info_;
  AstNode* ast;
  const char* sql_clause;
  int error_number;
};

/**
 * @brief AstStmtList is used to link every statement in one sql contains
 * multiple statement.
 * @details For example: select a from tb;select max(a) from tb2;
 */
class AstStmtList : public AstNode {
 public:
  AstStmtList(AstNodeType ast_node_type, AstNode* stmt, AstNode* next);
  ~AstStmtList();
  void Print(int level = 0) const;
  AstNode* stmt_;
  AstNode* next_;
};

#endif  // SQL_PARSER_AST_NODE_AST_NODE_H_
