// to compile run
// g++ hdd.c -o hdd -lkcgihtml -lkcgi

    #include <sys/types.h> /* size_t, ssize_t */
    #include <stdarg.h> /* va_list */
    #include <stddef.h> /* NULL */
    #include <stdint.h> /* int64_t */
    #include <kcgi.h>
    #include <kcgihtml.h>
    #include <stdio.h>



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



    static void process(struct kreq *r) {
      struct kpair *p;
//      khttp_puts(r, "<p>\n");
//      khttp_puts(r, "The string value is ");
//      if ((p = r->fieldmap[KEY_STRING]))
//        khttp_puts(r, p->parsed.s);
//      else if (r->fieldnmap[KEY_STRING])
//        khttp_puts(r, "<i>failed parse</i>");
//      else 
//        khttp_puts(r, "<i>not provided</i>");
//      khttp_puts(r, "</p>\n");
//      khttp_puts(r, "<p>\n");
//      khttp_puts(r, "Integer value is ");
//      p = r->fieldmap[KEY_INTEGER];
//      char str[50];
//      sprintf(str, "%d", p->parsed.i);
//      khttp_puts(r, str);
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

    }



    static void process_safe(struct kreq *r) {
      struct kpair *p;
      struct khtmlreq req;
      khtml_open(&req, r, 0);
      khtml_elem(&req, KELEM_P);
//      khtml_puts(&req, "The string value is ");
//      if ((p = r->fieldmap[KEY_STRING])) {
//        khtml_puts(&req, p->parsed.s);
//      } else if (r->fieldnmap[KEY_STRING]) {
//        khtml_elem(&req, KELEM_I);
//        khtml_puts(&req, "failed parse");
//      } else {
//        khtml_elem(&req, KELEM_I);
//        khtml_puts(&req, "not provided");
//      }
//      khttp_puts(r, "</p>\n");
//      khttp_puts(r, "<p>\n");
//      khttp_puts(r, "Integer value is ");
//      p = r->fieldmap[KEY_INTEGER];
//      char str[50];
//      sprintf(str, "%d", p->parsed.i);
//      khttp_puts(r, str);

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
//        process(&r);
      }
      khttp_free(&r);
      return 0;
    };


