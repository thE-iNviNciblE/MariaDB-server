#ifdef USE_PRAGMA_IMPLEMENTATION
#pragma implementation // gcc: Class implementation
#endif

#define MYSQL_SERVER
#include "my_global.h"
#include "mysql_version.h"
#include "sql_class.h"

// na sluchai vtorogo puti: 
//CHARSET_INFO* system_charset_info;
//pthread_key(THD*, THR_THD);
//pthread_attr_t connection_attrib;
//ulong max_connections;
//uint ha_open_options;
//uint max_digest_length;
//bool opt_bin_log;
//my_bool opt_userstat_running;
//MY_TMPDIR mysql_tmpdir_list;
//plugin_ref ha_lock_engine(THD *thd, const handlerton *hton)
//{
//  return NULL;
//}
//
//struct system_variables global_system_variables;
//scheduler_functions *thread_scheduler;
//struct my_rnd_struct sql_rand;
//Atomic_counter<query_id_t> global_query_id;
//mysql_mutex_t LOCK_global_system_variables;
//Query_cache query_cache;
//
//void mysql_audit_init_thd(THD *thd){}
//void debug_sync_init_thread(THD*){}
//const char *mysql_errno_to_sqlstate(uint mysql_errno){return NULL;}
//void Apc_target::init(mysql_mutex_t *target_mutex){}
//void Query_cache::abort(THD*, Query_cache_tls*){}
//void mysql_audit_notify(THD*, unsigned int, void const*){}
//LEX::LEX(){}
//const LEX_CSTRING null_clex_str=  {NULL, 0};




int main(int argc, char **argv)
{
  THD *thd;
  thd= new THD(0);

  delete thd;
  return 0;
}
