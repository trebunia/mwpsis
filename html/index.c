#include <sys/types.h> /* size_t, ssize_t */
#include <stdarg.h> /* va_list */
#include <stddef.h> /* NULL */
#include <stdint.h> /* int64_t */
#include <kcgi.h>

int main(void) {
    struct kreq r;
    const char *page = "index";
    if (KCGI_OK != khttp_parse(&r, NULL, 0, &page, 1, 0))
        return 0;
    khttp_head(&r, kresps[KRESP_STATUS],
        "%s", khttps[KHTTP_200]);
    khttp_head(&r, kresps[KRESP_CONTENT_TYPE],
        "%s", kmimetypes[KMIME_TEXT_HTML]);
    khttp_body(&r);
    khttp_puts(&r,"<!DOCTYPE html>\
    <html>\
    <head>\
    	<title>Solve your database design problems!</title>\
      	<link rel='stylesheet' type='text/css' href='style'>\
      </head>\
      <body>\
      	<div class='container'>\
      		<form id='form1' action='/cgi-bin/hdd'>\
      			<ul class='flex-outer'>\
      				<li class='input_with_label'>\
      					<label>Number of HDD 8TB drives:</label>\
      					<input type='text' name='HDD_8' value='15000'>\
      				</li>\
      				<li class='input_with_label'>\
      					<label>Number of HDD 6TB drives:</label>\
      					<input type='text' name='HDD_6' value='30000'>\
      				</li>\
      				<li class='input_with_label'>\
      					<label>Number of SSD 1TB drives:</label>\
      					<input type='text' name='SSD_1' value='10000'>\
      				</li>\
      				<li class='input_with_label'>\
      					<label>Number of SSD 512GB drives:</label>\
      					<input type='text' name='SSD_512' value='20000'>\
      				</li>\
      				<li class='input_with_label'>\
      					<label>Price for HDD in RAID1:</label>\
      					<input type='text' name='RAID1_HDD' value='0.5'>\
      				</li>\
      				<li class='input_with_label'>\
      					<label for='RAID5_HDD'>Price for HDD in RAID5:</label>\
      					<input type='text' id='RAID5_HDD' name='RAID5_HDD' value='0.1'></li>\
      				<li class='input_with_label'>\
      					<label>Price for HDD in RAID6:</label>\
      					<input type='text' name='RAID6_HDD' value='0.3'>\
      				</li>\
      				<li class='input_with_label'>\
      					<label>Price for SSD in RAID1:</label>\
      					<input type='text' name='RAID1_SSD' value='1.5'>\
      				</li>\
      				<li class='input_with_label'>\
      					<label>Price for SSD in RAID5:</label>\
      					<input type='text' name='RAID5_SSD' value='0.8'>\
      				</li>\
      				<li class='input_with_label'>\
      					<label>Price for SSD in RAID6:</label>\
      					<input type='text' name='RAID6_SSD' value='1.1'>\
      				</li>\
      				<li>\
      					<button type='submit'>Submit</button>\
      				</li>\
      			</ul>\
      		</form>\
      	</div>\
      </body>\
      </html>");


    khttp_free(&r);
    return 0;
}
