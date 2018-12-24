// to compile run
// g++ hdd.c -o hdd -lkcgihtml -lkcgi -L/usr/local/lib -lClp -L/usr/local/lib -lcoinglpk -ldl -lm -L/usr/local/lib -lCoinUtils -lm -L/usr/local/lib -lcoinglpk -ldl -lm -I/usr/include/cppconn -L/usr/lib -lmysqlcppconn

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

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>




enum key {
    KEY_HDD_8,
    KEY_HDD_6,
    KEY_SSD_1,
    KEY_SSD_512,
    KEY_RAID1_HDD,
    KEY_RAID5_HDD,
    KEY_RAID6_HDD,
    KEY_RAID1_SSD,
    KEY_RAID5_SSD,
    KEY_RAID6_SSD,
    KEY__MAX
};



static const struct kvalid keys[KEY__MAX] = {
    { kvalid_stringne, "HDD_8" },
    { kvalid_stringne, "HDD_6" },
    { kvalid_stringne, "SSD_1" },
    { kvalid_stringne, "SSD_512" },
    { kvalid_stringne, "RAID1_HDD" },
    { kvalid_stringne, "RAID5_HDD" },
    { kvalid_stringne, "RAID6_HDD" },
    { kvalid_stringne, "RAID1_SSD" },
    { kvalid_stringne, "RAID5_SSD" },
    { kvalid_stringne, "RAID6_SSD" }
};

static void generate_data(struct kreq *r){
	std::ofstream myfile;
	myfile.open ("/var/www/html/cgi-bin/data.txt");

	//generate disk number data
	myfile << "data;\n";
	myfile << "param N := 1 " << r->fieldmap[KEY_HDD_8]->parsed.s << "\n";
	myfile << "\t 2 " << r->fieldmap[KEY_HDD_6]->parsed.s << "\n";
	myfile << "\t 3 " << r->fieldmap[KEY_SSD_1]->parsed.s << "\n";
	myfile << "\t 4 " << r->fieldmap[KEY_SSD_512]->parsed.s << ";\n";
	myfile << "\n";

	//generate disk price data
	myfile << "param C : 1 2 3 4 := \n";
	myfile << "\t 1 " << r->fieldmap[KEY_RAID1_HDD]->parsed.s << " " << r->fieldmap[KEY_RAID1_HDD]->parsed.s << " " << r->fieldmap[KEY_RAID1_SSD]->parsed.s << " " << r->fieldmap[KEY_RAID1_SSD]->parsed.s << "\n";
    myfile << "\t 5 " << r->fieldmap[KEY_RAID5_HDD]->parsed.s << " " << r->fieldmap[KEY_RAID5_HDD]->parsed.s << " " << r->fieldmap[KEY_RAID5_SSD]->parsed.s << " " << r->fieldmap[KEY_RAID5_SSD]->parsed.s << "\n";
    myfile << "\t 6 " << r->fieldmap[KEY_RAID6_HDD]->parsed.s << " " << r->fieldmap[KEY_RAID6_HDD]->parsed.s << " " << r->fieldmap[KEY_RAID6_SSD]->parsed.s << " " << r->fieldmap[KEY_RAID6_SSD]->parsed.s << ";\n";
	myfile << "\n";

	//generate V
	myfile << "param V := 1 1\n\t2 1\n\t3 1\n\t4 1;\n\n";
	
	myfile << "param S := 1 1\n\t2 1\n\t3 1\n\t4 1;\n\n";

	myfile << "param R := 1 1\n\t5 1\n\t6 1;\n\n";
	myfile << "end;";
	myfile.close();
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

int exe_query(std::string query)
{   
  int res;
    try {
  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;

  /* Create a connection */
  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306", "kcgi", "toor");
  /* Connect to the MySQL test database */
  con->setSchema("kcgi");

  stmt = con->createStatement();
  res = stmt->execute(query.c_str());

  return res;

} catch (sql::SQLException &e) {
  std::cout << "# ERR: SQLException in " << __FILE__;
  std::cout << "(" << __FUNCTION__ << ") on line " \
     << __LINE__ << std::endl;
  std::cout << "# ERR: " << e.what(); 
  std::cout << " (MySQL error code: " << e.getErrorCode();
  std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
  return res;
}
}


static int running(){
	sql::ResultSet *res;
	res = run_query("select unique_id from optymalizacje where status = 'inprogress';");
	if (res->next()) {
		delete res;
		return 1;
	} else {
		delete res;
		return 0;
	}
}

std::string gen_random() {
    int len = 8;
    std::string s;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    srand(time(0));
    for (int i = 0; i < len; ++i) {
        s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return s;
}


static void optimization(struct kreq *r) {
 	ClpSimplex model;
 	int status;
	char* data;
	std::string line;
	std::string out;
    const char* filename = "/var/www/html/cgi-bin/model-projekt4.mod";
 	const char* data_file = "/var/www/html/cgi-bin/data.txt";
 	generate_data(r);
	system("/usr/bin/glpsol --math /var/www/html/cgi-bin/model-projekt4.mod -d /var/www/html/cgi-bin/data.txt --wmps /var/www/html/cgi-bin/model.mps >> /dev/null 2>&1");
	
	if (running() == 0){
		std::string unique_id;
		unique_id = gen_random();
		std::string query;
		query = "insert into optymalizacje (unique_id, status) values ('" + unique_id + "', 'inprogress');";
		exe_query(query);
		std::cout << "<p>Uruchamianie optymalizacji. Unikalny kod optymalizacji to " << unique_id;
		system("/usr/local/bin/cbc /var/www/html/cgi-bin/model.mps -max -solve -solu /var/www/html/cgi-bin/output.csv >> /dev/null 2>&1");
		query = "update optymalizacje set status = 'finished' where unique_id = '" + unique_id + "';";
		exe_query(query);
		std::cout << "<p>Optymalizacja (kod " << unique_id << ") zostala ukonczona";

	        std::ifstream myfile;
       		myfile.open("/var/www/html/cgi-bin/output.csv");
		out = "";
		if (myfile.is_open())
		  {
		    while ( getline (myfile,line) )
		    {
		      out += "\n<p>" + line + "\n";
		    }
		    myfile.close();
		    std::cout << out;
		  }

		else {
		     out += "Unable to open file"; 
		     std::cout << out;
		}
		exe_query("update optymalizacje set wynik = '" + out + "' where unique_id = '" + unique_id + "';");


	} else {
		std::cout << "<h1>Optymalizacja jest aktualnie uruchomiona</h1>";
	}
}

static void process_safe(struct kreq *r) {
	struct kpair *p;
	struct khtmlreq req;
	khtml_open(&req, r, 0);
	khtml_elem(&req, KELEM_P);
	khttp_puts(r, "<p>\n");
	khttp_puts(r, "The HDD_8 value is ");
    if ((p = r->fieldmap[KEY_HDD_8]))
    	khttp_puts(r, p->parsed.s);

    khttp_puts(r, "<p>\n");
    khttp_puts(r, "The HDD_6 value is ");
    if ((p = r->fieldmap[KEY_HDD_6]))
    	khttp_puts(r, p->parsed.s);

    khttp_puts(r, "<p>\n");
    khttp_puts(r, "The SSD_1 value is ");
    if ((p = r->fieldmap[KEY_SSD_1]))
    	khttp_puts(r, p->parsed.s);

    khttp_puts(r, "<p>\n");
    khttp_puts(r, "The SSD_512 value is ");
    if ((p = r->fieldmap[KEY_SSD_512]))
    	khttp_puts(r, p->parsed.s);

    khttp_puts(r, "<p>\n");
    khttp_puts(r, "The RAID1_HDD value is ");
    if ((p = r->fieldmap[KEY_RAID1_HDD]))
    	khttp_puts(r, p->parsed.s);
    khttp_puts(r, "<p>\n");
    khttp_puts(r, "The RAID5_HDD value is ");

    if ((p = r->fieldmap[KEY_RAID5_HDD]))
    	khttp_puts(r, p->parsed.s);
    khttp_puts(r, "<p>\n");
    khttp_puts(r, "The RAID6_HDD value is ");

    if ((p = r->fieldmap[KEY_RAID6_HDD]))
    	khttp_puts(r, p->parsed.s);
    khttp_puts(r, "<p>\n");
    khttp_puts(r, "The RAID1_SSD value is ");

    if ((p = r->fieldmap[KEY_RAID1_SSD]))
    	khttp_puts(r, p->parsed.s);
    khttp_puts(r, "<p>\n");
    khttp_puts(r, "The RAID5_SSD value is ");

    if ((p = r->fieldmap[KEY_RAID5_SSD]))
    	khttp_puts(r, p->parsed.s);

    khttp_puts(r, "<p>\n");
    khttp_puts(r, "The RAID6_SSD value is ");
    if ((p = r->fieldmap[KEY_RAID6_SSD]))
    	khttp_puts(r, p->parsed.s);

	optimization(r);
	khtml_close(&req);

}


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


