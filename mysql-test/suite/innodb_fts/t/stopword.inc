if ($stopword_stage == create_table)
{
--disable_query_log
set @dbug_stopword= '';
let $have_debug= `select version() like '%debug%'`;
if ($have_debug)
{
  set @dbug_tables= @@global.debug_dbug;
}
if ($MTR_COMBINATION_VERS_STOPWORD)
{
  set @dbug_stopword= '+d,sysvers_force,sysvers_hide';
  if (!$have_debug)
  {
    --skip Requires debug
  }
}
--enable_query_log

call mtr.add_suppression("\\[ERROR\\] InnoDB: user stopword table not_defined does not exist.");
call mtr.add_suppression("\\[ERROR\\] InnoDB: user stopword table test/user_stopword_session does not exist.");

select * from information_schema.innodb_ft_default_stopword;

# Create FTS table
eval CREATE TABLE articles (
        id INT UNSIGNED AUTO_INCREMENT NOT NULL PRIMARY KEY,
        title VARCHAR(200),
        body TEXT,
        FULLTEXT (title,body)
        )$create_options ENGINE=InnoDB;

# Insert six rows
INSERT INTO articles (title,body) VALUES
        ('MySQL Tutorial','DBMS stands for DataBase ...')  ,
        ('How To Use MySQL Well','After you went through a ...'),
        ('Optimizing MySQL','In this tutorial we will show ...'),
        ('1001 MySQL Tricks','1. Never run mysqld as root. 2. ...'),
        ('MySQL vs. YourSQL','In the following database comparison ...'),
        ('MySQL Security','When configured properly, MySQL ...');

# "the" is in the default stopword, it would not be selected
SELECT * FROM articles WHERE MATCH (title,body)
        AGAINST ('the' IN NATURAL LANGUAGE MODE);

# Provide user defined stopword table, if not (correctly) defined,
# it will be rejected
--error ER_WRONG_VALUE_FOR_VAR
set global innodb_ft_server_stopword_table = "not_defined";
set global innodb_ft_server_stopword_table = NULL;

# Define a correct formated user stopword table
if ($have_debug)
{
  --disable_query_log
  set debug_dbug= @dbug_stopword;
  --enable_query_log
}
create table user_stopword(value varchar(30)) engine = innodb;
if ($have_debug)
{
  --disable_query_log
  set debug_dbug= @dbug_tables;
  --enable_query_log
}

# The set operation should be successful
set global innodb_ft_server_stopword_table = "test/user_stopword";

drop index title on articles;

create fulltext index idx on articles(title, body);
}

if ($stopword_stage == select_1)
{
--error 0, ER_INDEX_CORRUPT
SELECT * FROM articles WHERE MATCH (title,body)
        AGAINST ('the' IN NATURAL LANGUAGE MODE);
--error 0, ER_INDEX_CORRUPT
SELECT * FROM articles WHERE MATCH (title,body)
        AGAINST ('this' IN NATURAL LANGUAGE MODE);

}
