--
-- PostgreSQL database dump
--

SET client_encoding = 'UNICODE';
SET check_function_bodies = false;

SET SESSION AUTHORIZATION 'postgres';

--
-- TOC entry 4 (OID 2200)
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
GRANT ALL ON SCHEMA public TO PUBLIC;


SET SESSION AUTHORIZATION 'ananas';

SET search_path = public, pg_catalog;

--
-- TOC entry 5 (OID 66705)
-- Name: uniques; Type: TABLE; Schema: public; Owner: ananas
--

CREATE TABLE uniques (
    id bigserial NOT NULL,
    otype integer,
    df character(1)
);


--
-- TOC entry 6 (OID 66712)
-- Name: a_journ; Type: TABLE; Schema: public; Owner: ananas
--

CREATE TABLE a_journ (
    id bigint NOT NULL,
    typej integer,
    idd bigint,
    typed integer,
    ddate timestamp without time zone,
    pnum character(254) NOT NULL,
    num integer,
    mf character(1),
    df character(1),
    cf character(1)
);


--
-- TOC entry 7 (OID 66725)
-- Name: usr; Type: TABLE; Schema: public; Owner: ananas
--

CREATE TABLE usr (
    id bigint NOT NULL,
    fname character(25),
    lname character(30),
    login character(20),
    "password" character(100)
);


--
-- TOC entry 8 (OID 66733)
-- Name: rl; Type: TABLE; Schema: public; Owner: ananas
--

CREATE TABLE rl (
    id bigint NOT NULL,
    name character(50)
);


--
-- TOC entry 9 (OID 66738)
-- Name: ce129; Type: TABLE; Schema: public; Owner: ananas
--

CREATE TABLE ce129 (
    id bigint NOT NULL,
    df character(1),
    idg bigint,
    ido bigint,
    uf134 character(120),
    uf138 character(30),
    uf136 character(120),
    uf642 numeric(2,1),
    uf644 numeric(2,1),
    uf819 character(254),
    uf1146 character(30)
);


--
-- TOC entry 10 (OID 66745)
-- Name: cg129; Type: TABLE; Schema: public; Owner: ananas
--

CREATE TABLE cg129 (
    id bigint NOT NULL,
    df character(1),
    "level" bigint,
    idp bigint,
    uf146 character(80)
);


--
-- TOC entry 11 (OID 66752)
-- Name: ce310; Type: TABLE; Schema: public; Owner: ananas
--

CREATE TABLE ce310 (
    id bigint NOT NULL,
    df character(1),
    idg bigint,
    ido bigint,
    uf315 character(60),
    uf317 character(30),
    uf776 character(100),
    uf778 character(200),
    uf780 character(100),
    uf782 character(6),
    uf784 character(30),
    uf786 character(30),
    uf788 character(254),
    uf790 character(100),
    uf792 character(100),
    uf794 character(100),
    uf796 character(100),
    uf798 character(254)
);


--
-- TOC entry 12 (OID 66762)
-- Name: cg310; Type: TABLE; Schema: public; Owner: ananas
--

CREATE TABLE cg310 (
    id bigint NOT NULL,
    df character(1),
    "level" bigint,
    idp bigint,
    uf638 character(150)
);


--
-- TOC entry 13 (OID 66769)
-- Name: ce828; Type: TABLE; Schema: public; Owner: ananas
--

CREATE TABLE ce828 (
    id bigint NOT NULL,
    df character(1),
    idg bigint,
    ido bigint,
    uf838 character(200),
    uf840 character(200)
);


--
-- TOC entry 14 (OID 66776)
-- Name: cg828; Type: TABLE; Schema: public; Owner: ananas
--

CREATE TABLE cg828 (
    id bigint NOT NULL,
    df character(1),
    "level" bigint,
    idp bigint,
    uf836 character(50)
);


--
-- TOC entry 15 (OID 66783)
-- Name: ce909; Type: TABLE; Schema: public; Owner: ananas
--

CREATE TABLE ce909 (
    id bigint NOT NULL,
    df character(1),
    idg bigint,
    ido bigint,
    uf917 character(100),
    uf921 numeric(3,0)
);


--
-- TOC entry 16 (OID 66790)
-- Name: cg909; Type: TABLE; Schema: public; Owner: ananas
--

CREATE TABLE cg909 (
    id bigint NOT NULL,
    df character(1),
    "level" bigint,
    idp bigint,
    uf919 character(100)
);


--
-- TOC entry 17 (OID 66797)
-- Name: dh576; Type: TABLE; Schema: public; Owner: ananas
--

CREATE TABLE dh576 (
    id bigint NOT NULL,
    uf582 character(100),
    uf584 timestamp without time zone,
    uf586 bigint,
    uf766 character(254),
    uf984 bigint
);


--
-- TOC entry 18 (OID 66801)
-- Name: dt576_588; Type: TABLE; Schema: public; Owner: ananas
--

CREATE TABLE dt576_588 (
    id bigint NOT NULL,
    idd bigint NOT NULL,
    ln bigint,
    uf589 bigint,
    uf591 numeric(12,0),
    uf593 numeric(12,2),
    uf768 numeric(12,2),
    uf770 numeric(12,2),
    uf772 numeric(12,2),
    uf774 numeric(12,2)
);


--
-- TOC entry 19 (OID 66807)
-- Name: dh101; Type: TABLE; Schema: public; Owner: ananas
--

CREATE TABLE dh101 (
    id bigint NOT NULL,
    uf121 character(100),
    uf123 timestamp without time zone,
    uf354 character(254),
    uf629 bigint,
    uf986 bigint
);


--
-- TOC entry 20 (OID 66811)
-- Name: dt101_126; Type: TABLE; Schema: public; Owner: ananas
--

CREATE TABLE dt101_126 (
    id bigint NOT NULL,
    idd bigint NOT NULL,
    ln bigint,
    uf127 bigint,
    uf140 numeric(10,0),
    uf142 numeric(10,2),
    uf356 character(254),
    uf448 numeric(10,2)
);


--
-- TOC entry 21 (OID 66817)
-- Name: dh874; Type: TABLE; Schema: public; Owner: ananas
--

CREATE TABLE dh874 (
    id bigint NOT NULL,
    uf880 character(100),
    uf882 timestamp without time zone,
    uf884 bigint
);


--
-- TOC entry 22 (OID 66821)
-- Name: dt874_886; Type: TABLE; Schema: public; Owner: ananas
--

CREATE TABLE dt874_886 (
    id bigint NOT NULL,
    idd bigint NOT NULL,
    ln bigint,
    uf887 bigint,
    uf889 character(50),
    uf890 numeric(10,0),
    uf892 numeric(12,2),
    uf895 numeric(12,2)
);


--
-- TOC entry 23 (OID 66827)
-- Name: dh988; Type: TABLE; Schema: public; Owner: ananas
--

CREATE TABLE dh988 (
    id bigint NOT NULL,
    uf994 numeric(12,0),
    uf996 timestamp without time zone,
    uf998 bigint,
    uf1000 character(200),
    uf1219 numeric(10,2)
);


--
-- TOC entry 24 (OID 66831)
-- Name: dh1002; Type: TABLE; Schema: public; Owner: ananas
--

CREATE TABLE dh1002 (
    id bigint NOT NULL,
    uf1221 character(50),
    uf1223 timestamp without time zone,
    uf1225 bigint,
    uf1227 character(200),
    uf1229 numeric(12,2),
    uf1231 character(200),
    uf1233 character(254)
);


--
-- TOC entry 25 (OID 66838)
-- Name: dh1051; Type: TABLE; Schema: public; Owner: ananas
--

CREATE TABLE dh1051 (
    id bigint NOT NULL,
    uf1124 numeric(10,0),
    uf1126 timestamp without time zone,
    uf1318 bigint,
    uf1320 numeric(10,2),
    uf1322 character(254)
);


--
-- TOC entry 26 (OID 66842)
-- Name: dh1061; Type: TABLE; Schema: public; Owner: ananas
--

CREATE TABLE dh1061 (
    id bigint NOT NULL,
    uf1129 character(100),
    uf1131 timestamp without time zone,
    uf1148 bigint,
    uf1150 numeric(12,2),
    uf1152 character(254)
);


--
-- TOC entry 27 (OID 66846)
-- Name: ra296; Type: TABLE; Schema: public; Owner: ananas
--

CREATE TABLE ra296 (
    id bigint NOT NULL,
    idd bigint,
    iddt bigint,
    ln bigint,
    date timestamp without time zone,
    uf814 numeric(10,0),
    uf1324 numeric(12,2),
    uf302 character(10),
    uf304 character(10),
    uf308 bigint,
    uf321 bigint,
    uf1144 bigint,
    uf298 character(200)
);


--
-- Data for TOC entry 104 (OID 66705)
-- Name: uniques; Type: TABLE DATA; Schema: public; Owner: ananas
--

COPY uniques (id, otype, df) FROM stdin;
\.


--
-- Data for TOC entry 105 (OID 66712)
-- Name: a_journ; Type: TABLE DATA; Schema: public; Owner: ananas
--

COPY a_journ (id, typej, idd, typed, ddate, pnum, num, mf, df, cf) FROM stdin;
\.


--
-- Data for TOC entry 106 (OID 66725)
-- Name: usr; Type: TABLE DATA; Schema: public; Owner: ananas
--

COPY usr (id, fname, lname, login, "password") FROM stdin;
\.


--
-- Data for TOC entry 107 (OID 66733)
-- Name: rl; Type: TABLE DATA; Schema: public; Owner: ananas
--

COPY rl (id, name) FROM stdin;
\.


--
-- Data for TOC entry 108 (OID 66738)
-- Name: ce129; Type: TABLE DATA; Schema: public; Owner: ananas
--

COPY ce129 (id, df, idg, ido, uf134, uf138, uf136, uf642, uf644, uf819, uf1146) FROM stdin;
\.


--
-- Data for TOC entry 109 (OID 66745)
-- Name: cg129; Type: TABLE DATA; Schema: public; Owner: ananas
--

COPY cg129 (id, df, "level", idp, uf146) FROM stdin;
\.


--
-- Data for TOC entry 110 (OID 66752)
-- Name: ce310; Type: TABLE DATA; Schema: public; Owner: ananas
--

COPY ce310 (id, df, idg, ido, uf315, uf317, uf776, uf778, uf780, uf782, uf784, uf786, uf788, uf790, uf792, uf794, uf796, uf798) FROM stdin;
\.


--
-- Data for TOC entry 111 (OID 66762)
-- Name: cg310; Type: TABLE DATA; Schema: public; Owner: ananas
--

COPY cg310 (id, df, "level", idp, uf638) FROM stdin;
\.


--
-- Data for TOC entry 112 (OID 66769)
-- Name: ce828; Type: TABLE DATA; Schema: public; Owner: ananas
--

COPY ce828 (id, df, idg, ido, uf838, uf840) FROM stdin;
\.


--
-- Data for TOC entry 113 (OID 66776)
-- Name: cg828; Type: TABLE DATA; Schema: public; Owner: ananas
--

COPY cg828 (id, df, "level", idp, uf836) FROM stdin;
\.


--
-- Data for TOC entry 114 (OID 66783)
-- Name: ce909; Type: TABLE DATA; Schema: public; Owner: ananas
--

COPY ce909 (id, df, idg, ido, uf917, uf921) FROM stdin;
\.


--
-- Data for TOC entry 115 (OID 66790)
-- Name: cg909; Type: TABLE DATA; Schema: public; Owner: ananas
--

COPY cg909 (id, df, "level", idp, uf919) FROM stdin;
\.


--
-- Data for TOC entry 116 (OID 66797)
-- Name: dh576; Type: TABLE DATA; Schema: public; Owner: ananas
--

COPY dh576 (id, uf582, uf584, uf586, uf766, uf984) FROM stdin;
\.


--
-- Data for TOC entry 117 (OID 66801)
-- Name: dt576_588; Type: TABLE DATA; Schema: public; Owner: ananas
--

COPY dt576_588 (id, idd, ln, uf589, uf591, uf593, uf768, uf770, uf772, uf774) FROM stdin;
\.


--
-- Data for TOC entry 118 (OID 66807)
-- Name: dh101; Type: TABLE DATA; Schema: public; Owner: ananas
--

COPY dh101 (id, uf121, uf123, uf354, uf629, uf986) FROM stdin;
\.


--
-- Data for TOC entry 119 (OID 66811)
-- Name: dt101_126; Type: TABLE DATA; Schema: public; Owner: ananas
--

COPY dt101_126 (id, idd, ln, uf127, uf140, uf142, uf356, uf448) FROM stdin;
\.


--
-- Data for TOC entry 120 (OID 66817)
-- Name: dh874; Type: TABLE DATA; Schema: public; Owner: ananas
--

COPY dh874 (id, uf880, uf882, uf884) FROM stdin;
\.


--
-- Data for TOC entry 121 (OID 66821)
-- Name: dt874_886; Type: TABLE DATA; Schema: public; Owner: ananas
--

COPY dt874_886 (id, idd, ln, uf887, uf889, uf890, uf892, uf895) FROM stdin;
\.


--
-- Data for TOC entry 122 (OID 66827)
-- Name: dh988; Type: TABLE DATA; Schema: public; Owner: ananas
--

COPY dh988 (id, uf994, uf996, uf998, uf1000, uf1219) FROM stdin;
\.


--
-- Data for TOC entry 123 (OID 66831)
-- Name: dh1002; Type: TABLE DATA; Schema: public; Owner: ananas
--

COPY dh1002 (id, uf1221, uf1223, uf1225, uf1227, uf1229, uf1231, uf1233) FROM stdin;
\.


--
-- Data for TOC entry 124 (OID 66838)
-- Name: dh1051; Type: TABLE DATA; Schema: public; Owner: ananas
--

COPY dh1051 (id, uf1124, uf1126, uf1318, uf1320, uf1322) FROM stdin;
\.


--
-- Data for TOC entry 125 (OID 66842)
-- Name: dh1061; Type: TABLE DATA; Schema: public; Owner: ananas
--

COPY dh1061 (id, uf1129, uf1131, uf1148, uf1150, uf1152) FROM stdin;
\.


--
-- Data for TOC entry 126 (OID 66846)
-- Name: ra296; Type: TABLE DATA; Schema: public; Owner: ananas
--

COPY ra296 (id, idd, iddt, ln, date, uf814, uf1324, uf302, uf304, uf308, uf321, uf1144, uf298) FROM stdin;
\.


--
-- TOC entry 29 (OID 66710)
-- Name: uniques_idx0; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX uniques_idx0 ON uniques USING btree (otype);


--
-- TOC entry 30 (OID 66711)
-- Name: uniques_idx1; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX uniques_idx1 ON uniques USING btree (df);


--
-- TOC entry 32 (OID 66716)
-- Name: a_journ_idx0; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX a_journ_idx0 ON a_journ USING btree (typej);


--
-- TOC entry 33 (OID 66717)
-- Name: a_journ_idx1; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX a_journ_idx1 ON a_journ USING btree (idd);


--
-- TOC entry 34 (OID 66718)
-- Name: a_journ_idx2; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX a_journ_idx2 ON a_journ USING btree (typed);


--
-- TOC entry 35 (OID 66719)
-- Name: a_journ_idx3; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX a_journ_idx3 ON a_journ USING btree (ddate);


--
-- TOC entry 36 (OID 66720)
-- Name: a_journ_idx4; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX a_journ_idx4 ON a_journ USING btree (pnum);


--
-- TOC entry 37 (OID 66721)
-- Name: a_journ_idx5; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX a_journ_idx5 ON a_journ USING btree (num);


--
-- TOC entry 38 (OID 66722)
-- Name: a_journ_idx6; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX a_journ_idx6 ON a_journ USING btree (mf);


--
-- TOC entry 39 (OID 66723)
-- Name: a_journ_idx7; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX a_journ_idx7 ON a_journ USING btree (df);


--
-- TOC entry 40 (OID 66724)
-- Name: a_journ_idx8; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX a_journ_idx8 ON a_journ USING btree (cf);


--
-- TOC entry 42 (OID 66729)
-- Name: usr_idx0; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX usr_idx0 ON usr USING btree (fname);


--
-- TOC entry 43 (OID 66730)
-- Name: usr_idx1; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX usr_idx1 ON usr USING btree (lname);


--
-- TOC entry 44 (OID 66731)
-- Name: usr_idx2; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX usr_idx2 ON usr USING btree (login);


--
-- TOC entry 45 (OID 66732)
-- Name: usr_idx3; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX usr_idx3 ON usr USING btree ("password");


--
-- TOC entry 47 (OID 66737)
-- Name: rl_idx0; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX rl_idx0 ON rl USING btree (name);


--
-- TOC entry 49 (OID 66742)
-- Name: ce129_idx0; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX ce129_idx0 ON ce129 USING btree (df);


--
-- TOC entry 50 (OID 66743)
-- Name: ce129_idx1; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX ce129_idx1 ON ce129 USING btree (idg);


--
-- TOC entry 51 (OID 66744)
-- Name: ce129_idx2; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX ce129_idx2 ON ce129 USING btree (ido);


--
-- TOC entry 53 (OID 66749)
-- Name: cg129_idx0; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX cg129_idx0 ON cg129 USING btree (df);


--
-- TOC entry 54 (OID 66750)
-- Name: cg129_idx1; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX cg129_idx1 ON cg129 USING btree ("level");


--
-- TOC entry 55 (OID 66751)
-- Name: cg129_idx2; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX cg129_idx2 ON cg129 USING btree (idp);


--
-- TOC entry 57 (OID 66759)
-- Name: ce310_idx0; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX ce310_idx0 ON ce310 USING btree (df);


--
-- TOC entry 58 (OID 66760)
-- Name: ce310_idx1; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX ce310_idx1 ON ce310 USING btree (idg);


--
-- TOC entry 59 (OID 66761)
-- Name: ce310_idx2; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX ce310_idx2 ON ce310 USING btree (ido);


--
-- TOC entry 61 (OID 66766)
-- Name: cg310_idx0; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX cg310_idx0 ON cg310 USING btree (df);


--
-- TOC entry 62 (OID 66767)
-- Name: cg310_idx1; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX cg310_idx1 ON cg310 USING btree ("level");


--
-- TOC entry 63 (OID 66768)
-- Name: cg310_idx2; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX cg310_idx2 ON cg310 USING btree (idp);


--
-- TOC entry 65 (OID 66773)
-- Name: ce828_idx0; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX ce828_idx0 ON ce828 USING btree (df);


--
-- TOC entry 66 (OID 66774)
-- Name: ce828_idx1; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX ce828_idx1 ON ce828 USING btree (idg);


--
-- TOC entry 67 (OID 66775)
-- Name: ce828_idx2; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX ce828_idx2 ON ce828 USING btree (ido);


--
-- TOC entry 69 (OID 66780)
-- Name: cg828_idx0; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX cg828_idx0 ON cg828 USING btree (df);


--
-- TOC entry 70 (OID 66781)
-- Name: cg828_idx1; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX cg828_idx1 ON cg828 USING btree ("level");


--
-- TOC entry 71 (OID 66782)
-- Name: cg828_idx2; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX cg828_idx2 ON cg828 USING btree (idp);


--
-- TOC entry 73 (OID 66787)
-- Name: ce909_idx0; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX ce909_idx0 ON ce909 USING btree (df);


--
-- TOC entry 74 (OID 66788)
-- Name: ce909_idx1; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX ce909_idx1 ON ce909 USING btree (idg);


--
-- TOC entry 75 (OID 66789)
-- Name: ce909_idx2; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX ce909_idx2 ON ce909 USING btree (ido);


--
-- TOC entry 77 (OID 66794)
-- Name: cg909_idx0; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX cg909_idx0 ON cg909 USING btree (df);


--
-- TOC entry 78 (OID 66795)
-- Name: cg909_idx1; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX cg909_idx1 ON cg909 USING btree ("level");


--
-- TOC entry 79 (OID 66796)
-- Name: cg909_idx2; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX cg909_idx2 ON cg909 USING btree (idp);


--
-- TOC entry 82 (OID 66805)
-- Name: dt576_588_idx0; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX dt576_588_idx0 ON dt576_588 USING btree (idd);


--
-- TOC entry 83 (OID 66806)
-- Name: dt576_588_idx1; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX dt576_588_idx1 ON dt576_588 USING btree (ln);


--
-- TOC entry 86 (OID 66815)
-- Name: dt101_126_idx0; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX dt101_126_idx0 ON dt101_126 USING btree (idd);


--
-- TOC entry 87 (OID 66816)
-- Name: dt101_126_idx1; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX dt101_126_idx1 ON dt101_126 USING btree (ln);


--
-- TOC entry 90 (OID 66825)
-- Name: dt874_886_idx0; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX dt874_886_idx0 ON dt874_886 USING btree (idd);


--
-- TOC entry 91 (OID 66826)
-- Name: dt874_886_idx1; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX dt874_886_idx1 ON dt874_886 USING btree (ln);


--
-- TOC entry 97 (OID 66850)
-- Name: ra296_idx0; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX ra296_idx0 ON ra296 USING btree (idd);


--
-- TOC entry 98 (OID 66851)
-- Name: ra296_idx1; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX ra296_idx1 ON ra296 USING btree (iddt);


--
-- TOC entry 99 (OID 66852)
-- Name: ra296_idx2; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX ra296_idx2 ON ra296 USING btree (ln);


--
-- TOC entry 100 (OID 66853)
-- Name: ra296_idx3; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX ra296_idx3 ON ra296 USING btree (date);


--
-- TOC entry 101 (OID 66854)
-- Name: ra296_idx4; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX ra296_idx4 ON ra296 USING btree (uf814);


--
-- TOC entry 102 (OID 66855)
-- Name: ra296_idx5; Type: INDEX; Schema: public; Owner: ananas
--

CREATE INDEX ra296_idx5 ON ra296 USING btree (uf1324);


--
-- TOC entry 31 (OID 66708)
-- Name: uniques_pkey; Type: CONSTRAINT; Schema: public; Owner: ananas
--

ALTER TABLE ONLY uniques
    ADD CONSTRAINT uniques_pkey PRIMARY KEY (id);


--
-- TOC entry 41 (OID 66714)
-- Name: a_journ_pkey; Type: CONSTRAINT; Schema: public; Owner: ananas
--

ALTER TABLE ONLY a_journ
    ADD CONSTRAINT a_journ_pkey PRIMARY KEY (id);


--
-- TOC entry 46 (OID 66727)
-- Name: usr_pkey; Type: CONSTRAINT; Schema: public; Owner: ananas
--

ALTER TABLE ONLY usr
    ADD CONSTRAINT usr_pkey PRIMARY KEY (id);


--
-- TOC entry 48 (OID 66735)
-- Name: rl_pkey; Type: CONSTRAINT; Schema: public; Owner: ananas
--

ALTER TABLE ONLY rl
    ADD CONSTRAINT rl_pkey PRIMARY KEY (id);


--
-- TOC entry 52 (OID 66740)
-- Name: ce129_pkey; Type: CONSTRAINT; Schema: public; Owner: ananas
--

ALTER TABLE ONLY ce129
    ADD CONSTRAINT ce129_pkey PRIMARY KEY (id);


--
-- TOC entry 56 (OID 66747)
-- Name: cg129_pkey; Type: CONSTRAINT; Schema: public; Owner: ananas
--

ALTER TABLE ONLY cg129
    ADD CONSTRAINT cg129_pkey PRIMARY KEY (id);


--
-- TOC entry 60 (OID 66757)
-- Name: ce310_pkey; Type: CONSTRAINT; Schema: public; Owner: ananas
--

ALTER TABLE ONLY ce310
    ADD CONSTRAINT ce310_pkey PRIMARY KEY (id);


--
-- TOC entry 64 (OID 66764)
-- Name: cg310_pkey; Type: CONSTRAINT; Schema: public; Owner: ananas
--

ALTER TABLE ONLY cg310
    ADD CONSTRAINT cg310_pkey PRIMARY KEY (id);


--
-- TOC entry 68 (OID 66771)
-- Name: ce828_pkey; Type: CONSTRAINT; Schema: public; Owner: ananas
--

ALTER TABLE ONLY ce828
    ADD CONSTRAINT ce828_pkey PRIMARY KEY (id);


--
-- TOC entry 72 (OID 66778)
-- Name: cg828_pkey; Type: CONSTRAINT; Schema: public; Owner: ananas
--

ALTER TABLE ONLY cg828
    ADD CONSTRAINT cg828_pkey PRIMARY KEY (id);


--
-- TOC entry 76 (OID 66785)
-- Name: ce909_pkey; Type: CONSTRAINT; Schema: public; Owner: ananas
--

ALTER TABLE ONLY ce909
    ADD CONSTRAINT ce909_pkey PRIMARY KEY (id);


--
-- TOC entry 80 (OID 66792)
-- Name: cg909_pkey; Type: CONSTRAINT; Schema: public; Owner: ananas
--

ALTER TABLE ONLY cg909
    ADD CONSTRAINT cg909_pkey PRIMARY KEY (id);


--
-- TOC entry 81 (OID 66799)
-- Name: dh576_pkey; Type: CONSTRAINT; Schema: public; Owner: ananas
--

ALTER TABLE ONLY dh576
    ADD CONSTRAINT dh576_pkey PRIMARY KEY (id);


--
-- TOC entry 84 (OID 66803)
-- Name: dt576_588_pkey; Type: CONSTRAINT; Schema: public; Owner: ananas
--

ALTER TABLE ONLY dt576_588
    ADD CONSTRAINT dt576_588_pkey PRIMARY KEY (id);


--
-- TOC entry 85 (OID 66809)
-- Name: dh101_pkey; Type: CONSTRAINT; Schema: public; Owner: ananas
--

ALTER TABLE ONLY dh101
    ADD CONSTRAINT dh101_pkey PRIMARY KEY (id);


--
-- TOC entry 88 (OID 66813)
-- Name: dt101_126_pkey; Type: CONSTRAINT; Schema: public; Owner: ananas
--

ALTER TABLE ONLY dt101_126
    ADD CONSTRAINT dt101_126_pkey PRIMARY KEY (id);


--
-- TOC entry 89 (OID 66819)
-- Name: dh874_pkey; Type: CONSTRAINT; Schema: public; Owner: ananas
--

ALTER TABLE ONLY dh874
    ADD CONSTRAINT dh874_pkey PRIMARY KEY (id);


--
-- TOC entry 92 (OID 66823)
-- Name: dt874_886_pkey; Type: CONSTRAINT; Schema: public; Owner: ananas
--

ALTER TABLE ONLY dt874_886
    ADD CONSTRAINT dt874_886_pkey PRIMARY KEY (id);


--
-- TOC entry 93 (OID 66829)
-- Name: dh988_pkey; Type: CONSTRAINT; Schema: public; Owner: ananas
--

ALTER TABLE ONLY dh988
    ADD CONSTRAINT dh988_pkey PRIMARY KEY (id);


--
-- TOC entry 94 (OID 66836)
-- Name: dh1002_pkey; Type: CONSTRAINT; Schema: public; Owner: ananas
--

ALTER TABLE ONLY dh1002
    ADD CONSTRAINT dh1002_pkey PRIMARY KEY (id);


--
-- TOC entry 95 (OID 66840)
-- Name: dh1051_pkey; Type: CONSTRAINT; Schema: public; Owner: ananas
--

ALTER TABLE ONLY dh1051
    ADD CONSTRAINT dh1051_pkey PRIMARY KEY (id);


--
-- TOC entry 96 (OID 66844)
-- Name: dh1061_pkey; Type: CONSTRAINT; Schema: public; Owner: ananas
--

ALTER TABLE ONLY dh1061
    ADD CONSTRAINT dh1061_pkey PRIMARY KEY (id);


--
-- TOC entry 103 (OID 66848)
-- Name: ra296_pkey; Type: CONSTRAINT; Schema: public; Owner: ananas
--

ALTER TABLE ONLY ra296
    ADD CONSTRAINT ra296_pkey PRIMARY KEY (id);


--
-- TOC entry 28 (OID 66703)
-- Name: uniques_id_seq; Type: SEQUENCE SET; Schema: public; Owner: ananas
--

SELECT pg_catalog.setval('uniques_id_seq', 1, false);


SET SESSION AUTHORIZATION 'postgres';

--
-- TOC entry 3 (OID 2200)
-- Name: SCHEMA public; Type: COMMENT; Schema: -; Owner: postgres
--

COMMENT ON SCHEMA public IS 'Standard public schema';


