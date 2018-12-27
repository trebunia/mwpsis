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
    { kvalid_int, "HDD_8" },
    { kvalid_int, "HDD_6" },
    { kvalid_int, "SSD_1" },
    { kvalid_int, "SSD_512" },
    { kvalid_double, "RAID1_HDD" },
    { kvalid_double, "RAID5_HDD" },
    { kvalid_double, "RAID6_HDD" },
    { kvalid_double, "RAID1_SSD" },
    { kvalid_double, "RAID5_SSD" },
    { kvalid_double, "RAID6_SSD" }
};

bool generate_data(struct kreq *r){
	try {
	std::ofstream myfile;
	myfile.open ("/var/www/html/cgi-bin/data.txt");

	if ( r->fieldmap[KEY_HDD_8] && r->fieldmap[KEY_HDD_6] && r->fieldmap[KEY_SSD_1] && r->fieldmap[KEY_SSD_512] && r->fieldmap[KEY_RAID1_HDD] && r->fieldmap[KEY_RAID5_HDD] && r->fieldmap[KEY_RAID6_HDD] && r->fieldmap[KEY_RAID1_SSD] && r->fieldmap[KEY_RAID5_SSD] && r->fieldmap[KEY_RAID6_SSD] ) {

	//generate disk number data
	myfile << "data;\n";
	myfile << "param N := 1 " << r->fieldmap[KEY_HDD_8]->parsed.i << "\n";
	myfile << "\t 2 " << r->fieldmap[KEY_HDD_6]->parsed.i << "\n";
	myfile << "\t 3 " << r->fieldmap[KEY_SSD_1]->parsed.i << "\n";
	myfile << "\t 4 " << r->fieldmap[KEY_SSD_512]->parsed.i << ";\n";
	myfile << "\n";

	//generate disk price data
	myfile << "param C : 1 2 3 4 := \n";
	myfile << "\t 1 " << r->fieldmap[KEY_RAID1_HDD]->parsed.d << " " << r->fieldmap[KEY_RAID1_HDD]->parsed.d << " " << r->fieldmap[KEY_RAID1_SSD]->parsed.d << " " << r->fieldmap[KEY_RAID1_SSD]->parsed.d << "\n";
    myfile << "\t 5 " << r->fieldmap[KEY_RAID5_HDD]->parsed.d << " " << r->fieldmap[KEY_RAID5_HDD]->parsed.d << " " << r->fieldmap[KEY_RAID5_SSD]->parsed.d << " " << r->fieldmap[KEY_RAID5_SSD]->parsed.d << "\n";
    myfile << "\t 6 " << r->fieldmap[KEY_RAID6_HDD]->parsed.d << " " << r->fieldmap[KEY_RAID6_HDD]->parsed.d << " " << r->fieldmap[KEY_RAID6_SSD]->parsed.d << " " << r->fieldmap[KEY_RAID6_SSD]->parsed.d << ";\n";
	myfile << "\n";

	//generate V
	myfile << "param V := 1 1\n\t2 1\n\t3 1\n\t4 1;\n\n";

	myfile << "param S := 1 1\n\t2 1\n\t3 1\n\t4 1;\n\n";

	myfile << "param R := 1 1\n\t5 1\n\t6 1;\n\n";
	myfile << "end;";
	myfile.close();

	return 0;

	} else {
		std::cout << "<!DOCTYPE html> \
    				<html> \
    				<head> \
    				<title>Solve your database design problems!</title> \
            <meta charset=\"UTF-8\">\
    				<link rel=\"stylesheet\" type=\"text/css\" href=\"../style.css\"> \
    				</head> \
    				<body> \
            Niepoprawnie wprowadzone parametry <br>\
            <a href=\"index\">Powrót do strony głównej </a>\
    				</body>\
    				</html>";

		return 1;
	}
	} catch (...) {
		std::cout << "Generowanie danych do symulacji nie udalo sie";
	}
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

	sql::ResultSet *res;
	res = run_query("select unique_id from optymalizacje where unique_id = '" + s + "';");

	// jesli wylosowany ID juz istnieje to losuj nowy dopoki nie bedzie unikalny

	while(res->next()) {
		delete res;
	    srand(time(0));
		s = "";
   		for (int i = 0; i < len; ++i) {
       		 s += alphanum[rand() % (sizeof(alphanum) - 1)];
    	}
		res = run_query("select unique_id from optymalizacje where unique_id = '" + s + "';");
	}
	delete res;
    return s;
}


static void print_loading(){
sql::ResultSet *res;
res = run_query("select unique_id, start_time from optymalizacje where status = 'inprogress';");
res->next();
std::cout << "<!DOCTYPE html> \
				<html> \
				<head> \
				<title>Solve your database design problems!</title> \
				<link rel=\"stylesheet\" type=\"text/css\" href=\"../style.css\"> \
				</head> \
				<body> \
				<div class=\"container\"> \
				<div id=loading_text> \
				<p id=\"text1\">Your request is being processed. </p>\
				<p id=\"text2\"> Please wait, it may take a while... </p>\
				<div class=\"loader\"></div>\
				<p id=\"start_time\">Solver already running for: "
                << res->getString("unique_id")
				<< "</p> Optimalization start time: "
                << res->getString("start_time")
			    << "</div> \
				</div> \
				</body>\
				</html>";
	delete res;
}

static void print_results(std::string msg){
std::cout << "<!DOCTYPE html> \
			<html> \
			<head> \
				<title>Solve your database design problems!</title> \
				<link rel=\"stylesheet\" type=\"text/css\" href=\"../style.css\"> \
			</head> \
			<body> \
				<div id=\"container\">"
		  << msg ;
			"</div> \
			</body> \
			</html>";

}

static void optimization(struct kreq *r) {
 	int status;
	char* data;
	std::string line;
	std::string out;
    const char* filename = "/var/www/html/cgi-bin/model-projekt4.mod";
 	const char* data_file = "/var/www/html/cgi-bin/data.txt";
 	if (generate_data(r) == 0) {

		if (system("/usr/bin/glpsol --math /var/www/html/cgi-bin/model-projekt4.mod -d /var/www/html/cgi-bin/data.txt --wmps /var/www/html/cgi-bin/model.mps >> /dev/null 2>&1") == 0) {
			std::string unique_id;
			unique_id = gen_random();
			std::string query;
			query = "insert into optymalizacje (unique_id, status) values ('" + unique_id + "', 'inprogress');";
			exe_query(query);
			print_results("<p>Uruchamianie optymalizacji. Unikalny kod optymalizacji to " + unique_id);
			system("/usr/local/bin/cbc /var/www/html/cgi-bin/model.mps -max -solve -solu /var/www/html/cgi-bin/output.csv >> /dev/null 2>&1");
			query = "update optymalizacje set status = 'finished' where unique_id = '" + unique_id + "';";
			exe_query(query);
			std::string msg;
			msg = "<p>Optymalizacja (kod " + unique_id + ") zostala ukonczona";

			std::ifstream myfile;
		    myfile.open("/var/www/html/cgi-bin/output.csv");
			out = "";
			if (myfile.is_open())
				{
				 while ( getline (myfile,line) )
				 	{
				      msg += "\n<p>" + line + "\n";
				    }
				  myfile.close();
				  print_results(msg);
				}

			else {
				msg += "Unable to open file";
				print_results(msg);
				}
			exe_query("update optymalizacje set wynik = '" + out + "' where unique_id = '" + unique_id + "';");
			}
	}

}

static void process_safe(struct kreq *r) {
	struct kpair *p;
	struct khtmlreq req;
	khtml_open(&req, r, 0);
	khtml_elem(&req, KELEM_P);

	if (running() == 0) {
		optimization(r);
	} else {
        print_loading();
	}

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
