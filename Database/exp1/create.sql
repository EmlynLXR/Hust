use DBexp;
/*建表*/

create table USERS(
	UID INT,
	NAME VARCHAR(255),
	SEX VARCHAR(255),
	BYEAR INT,
	CITY VARCHAR(255),
	primary key(UID)	
);

create table LABEL(
	LID INT ,
	LNAME VARCHAR(255),
	primary key(LID)
);

create table MBLOG(
	BID INT,
	TITLE VARCHAR(255),
	UID INT,
	PYEAR INT,
	PMONTH INT,
	PDAY INT,
	CONT VARCHAR(1024),
	primary key(BID),
	--constraint C1 foreign key(UID) references USERS(UID) on delete cascade on update cascade
	--若在此处设置外键，则于thumb之中的主键外键设置产生多重级联
);

create table B_L(
	BID INT,
	LID INT,
	primary key(BID,LID),
	constraint C2 foreign key(BID)references MBLOG(BID)on delete cascade on update cascade,
	constraint C3 foreign key(LID)references LABEL(LID)on delete cascade on update cascade
);

create table FOLLOW(
	UID INT,
	UIDFLED INT,
	primary key(UID,UIDFLED),
	constraint C4 foreign key(UID)references USERS(UID),
	constraint C5 foreign key(UIDFLED)references USERS(UID)
);

create table FRIENDS(
	UID INT,
	FUID INT,
	primary key(UID,FUID),
	constraint C6 foreign key(UID)references USERS(UID),
	constraint C7 foreign key(FUID)references USERS(UID)
);

create table SUB(
	UID INT,
	LID INT,
	primary key(UID,LID),
	constraint C8 foreign key(UID)references USERS(UID)on delete cascade on update cascade,
	constraint C9 foreign key(LID)references LABEL(LID)on delete cascade on update cascade
);

create table THUMB(
	UID INT,
	BID INT,
	primary key(UID,BID),
	constraint C10 foreign key(UID)references USERS(UID)on delete cascade on update cascade,
	constraint C11 foreign key(BID)references MBLOG(BID)on delete cascade on update cascade
);

create table TOPDAY(
	TYEAR INT,
	TMONTH INT,
	TDAY INT,
	BID INT,
	TNO INT,
	constraint C12 foreign key(BID)references MBLOG(BID)on delete cascade on update cascade
);


