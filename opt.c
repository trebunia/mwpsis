// g++ opt.c -o opt -ldl -lm -I/usr/include/cppconn -L/usr/lib -lmysqlcppconn -lkcgihtml -lkcgi -L/usr/local/lib -lClp -L/usr/local/lib -lcoinglpk -ldl -lm -L/usr/local/lib -lCoinUtils -lm -L/usr/local/lib -lcoinglpk -ldl -lm 
#include <sys/types.h> /* size_t, ssize_t */
#include <stdarg.h> /* va_list */
#include <stddef.h> /* NULL */
#include <stdint.h> /* int64_t */
#include <kcgi.h>
#include <stdlib.h>
#include <kcgihtml.h>
#include <stdio.h>
#include <coin/ClpSimplex.hpp>
#include <coin/CoinUtilsConfig.h>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
#include "mysql_connection.h"
#include <regex>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>



enum key {
	KEY_RES,
    KEY__MAX
};



static const struct kvalid keys[KEY__MAX] = {
	{ kvalid_stringne, "RES" }
};


enum page {
  PAGE_INDEX,
  PAGE__MAX
};
const char *const pages[PAGE__MAX] = {
  "index", /* PAGE_INDEX */
};



static enum khttp sanitise(const struct kreq *r) {
  if (PAGE_INDEX != r->page)
    return KHTTP_404;
  else if ('\0' != *r->path) /* no index/xxxx */
    return KHTTP_404;
  else if (KMIME_TEXT_HTML != r->mime)
    return KHTTP_404;
  else if (KMETHOD_GET != r->method)
    return KHTTP_405;
  return KHTTP_200;
}

sql::ResultSet* run_query(std::string query)
{
    try {
  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::ResultSet *res;

  /* Create a connection */
  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306", "kcgi", "toor");
  /* Connect to the MySQL test database */
  con->setSchema("kcgi");

  stmt = con->createStatement();
  res = stmt->executeQuery(query.c_str());

  return res;

} catch (sql::SQLException &e) {
  std::cout << "# ERR: SQLException in " << __FILE__;
  std::cout << "(" << __FUNCTION__ << ") on line " \
     << __LINE__ << std::endl;
  std::cout << "# ERR: " << e.what();
  std::cout << " (MySQL error code: " << e.getErrorCode();
  std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
}
}


int print_res(struct kreq *r) {
sql::ResultSet *res;


if ( r->fieldmap[KEY_RES] ){
	std::string resid;
	resid = r->fieldmap[KEY_RES]->parsed.s;
	std::regex reg("[a-zA-Z0-9]{8}");
	if (std::regex_match(resid, reg) ){

	char query [500] = {0};
	strcat(query, "select wynik from optymalizacje where unique_id = '");
	strcat(query,  r->fieldmap[KEY_RES]->parsed.s);
	strcat(query, "';");

	res = run_query(query);
	if (res->next()) {
		std::cout << "<!DOCTYPE html> \
	                    <html> \
	                    <head> \
	                    <link rel=\"stylesheet\" type=\"text/css\" href=\"../style.css\"> \
	                    <title>Solve your database design problems!</title> \
	            <meta charset=\"UTF-8\">\
	                    </head> \
	                    <body>" ;
	std::cout << "<p>" << res->getString("wynik") << "</p>";
	
	std::cout << "</body> \
				</html>";
	}
	} else {
	    std::cout << "<!DOCTYPE html> \
             <html> \
             <head> \
             <link rel=\"stylesheet\" type=\"text/css\" href=\"../style.css\"> \
             <title>Solve your database design problems!</title> \
           <meta charset=\"UTF-8\">\
             </head> \
             <body> \
            <p> Nie ma takiego ID </p> \
            </body> \
            </html> ";
	}
} else {
    std::cout << "<!DOCTYPE html> \
             <html> \
             <head> \
             <link rel=\"stylesheet\" type=\"text/css\" href=\"../style.css\"> \
             <title>Solve your database design problems!</title> \
           <meta charset=\"UTF-8\">\
             </head> \
             <body> \
			<p> Nie ma takiego ID </p> \
			</body> \
			</html> ";


}
return 0;
}




static void process_safe(struct kreq *r) {
    struct kpair *p;
    struct khtmlreq req;
    khtml_open(&req, r, 0);
    khtml_elem(&req, KELEM_P);
    print_res(r);

    khtml_close(&req);

}



int main(void) {
  struct kreq r;
  enum khttp er;
  if (KCGI_OK != khttp_parse(&r, keys, KEY__MAX,
      pages, PAGE__MAX, PAGE_INDEX))
    return 0;
  if (KHTTP_200 != (er = sanitise(&r))) {
    khttp_head(&r, kresps[KRESP_STATUS],
      "%s", khttps[er]);
    khttp_head(&r, kresps[KRESP_CONTENT_TYPE],
      "%s", kmimetypes[KMIME_TEXT_PLAIN]);
    khttp_body(&r);
    if (KMIME_TEXT_HTML == r.mime)
      khttp_puts(&r, "Could not service request.");
  } else {
    khttp_head(&r, kresps[KRESP_STATUS],
      "%s", khttps[KHTTP_200]);
    khttp_head(&r, kresps[KRESP_CONTENT_TYPE],
      "%s", kmimetypes[r.mime]);
    khttp_body(&r);
    process_safe(&r);
  }
  khttp_free(&r);
  return 0;
};
