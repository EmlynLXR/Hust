use DBexp;
Go

insert into USERS(UID,NAME,SEX,BYEAR,CITY) values (1,'王一','男',2001,'武汉');
insert into USERS(UID,NAME,SEX,BYEAR,CITY) values (2,'李二','女',2001,'郑州');
insert into USERS(UID,NAME,SEX,BYEAR,CITY) values (3,'张三','男',2000,'许昌');
insert into USERS(UID,NAME,SEX,BYEAR,CITY) values (4,'孙四','女',1999,'武汉');
insert into USERS(UID,NAME,SEX,BYEAR,CITY) values (5,'刘五','男',2000,'昆明');
insert into USERS(UID,NAME,SEX,BYEAR,CITY) values (6,'吴六','男',2001,'武汉');
insert into USERS(UID,NAME,SEX,BYEAR,CITY) values (7,'柳七','男',2011,'郑州');

insert into LABEL(LID,LNAME) values(1,'文学');
insert into LABEL(LID,LNAME) values(2,'艺术');
insert into LABEL(LID,LNAME) values(3,'军事');
insert into LABEL(LID,LNAME) values(4,'生活');

insert into MBLOG(BID,TITLE,UID,PYEAR,PMONTH,PDAY,CONT) values (1,null,1,2019,4,22,'人过的日子必是一日遇佛，一日遇魔。——贾平凹 《老生》');
insert into B_L(BID,LID) values (1,1);
insert into MBLOG(BID,TITLE,UID,PYEAR,PMONTH,PDAY,CONT) values (2,'微博艺术家扶持推广计划',2,2019,4,22,'NO.161创作者：李卓（微博@028李卓  ）作者简介：毕业于四川美术学院，现任教于四川师范大学美术学院。');
insert into B_L(BID,LID) values (2,2);
insert into MBLOG(BID,TITLE,UID,PYEAR,PMONTH,PDAY,CONT) values (3,null,3,2019,4,23,'国产航母挂旗了[吃瓜]#中国军情# 图片@热武器时代的爱情故事 ​​​​');
insert into B_L(BID,LID) values (3,3);
insert into MBLOG(BID,TITLE,UID,PYEAR,PMONTH,PDAY,CONT) values (4,'他是中国器官移植开创者，95岁去世捐出眼角膜',4,2019,4,24,'16日，中国器官移植开创者之一、华中科技大学同济医院教授夏穗生去世，享年95岁。家人遵从夏老生前遗愿捐献角膜，还代他捐款100万元用于医学研究。从医几十年，他用130次动物的实验打开中国器官移植事业的大门；培养器官移植人才；建立以公民捐献为唯一来源的器官移植体系……致敬，送别！');
insert into B_L(BID,LID) values (4,4);
insert into MBLOG(BID,TITLE,UID,PYEAR,PMONTH,PDAY,CONT) values (5,'华中科技大学',5,2019,4,25,'相醉于晚亭。');
insert into B_L(BID,LID) values (5,4);
insert into MBLOG(BID,TITLE,UID,PYEAR,PMONTH,PDAY,CONT) values (6,'武汉，你好',5,2019,4,25,'相醉于晚亭。');
insert into B_L(BID,LID) values (6,4);
insert into MBLOG(BID,TITLE,UID,PYEAR,PMONTH,PDAY,CONT) values (7,'最多地铁站',7,2019,4,26,'地铁站最多的城市');
insert into B_L(BID,LID) values (7,4);



insert into FOLLOW(UID,UIDFLED) values (1,2);
insert into FOLLOW(UID,UIDFLED) values (1,3);
insert into FOLLOW(UID,UIDFLED) values (1,5);
insert into FOLLOW(UID,UIDFLED) values (2,1);
insert into FOLLOW(UID,UIDFLED) values (2,3);
insert into FOLLOW(UID,UIDFLED) values (2,4);
insert into FOLLOW(UID,UIDFLED) values (3,2);
insert into FOLLOW(UID,UIDFLED) values (3,5);
insert into FOLLOW(UID,UIDFLED) values (4,1);
insert into FOLLOW(UID,UIDFLED) values (4,5);
insert into FOLLOW(UID,UIDFLED) values (5,4);
insert into FOLLOW(UID,UIDFLED) values (5,2);

insert into FRIENDS(UID,FUID) values (1,2),(2,1);
insert into FRIENDS(UID,FUID) values (1,3),(3,1);
insert into FRIENDS(UID,FUID) values (1,4),(4,1);
insert into FRIENDS(UID,FUID) values (2,4),(4,2);
insert into FRIENDS(UID,FUID) values (2,3),(3,2);
insert into FRIENDS(UID,FUID) values (3,4),(4,3);
insert into FRIENDS(UID,FUID) values (3,5),(5,3);

insert into SUB(UID,LID) values (1,1);
insert into SUB(UID,LID) values (1,2);
insert into SUB(UID,LID) values (2,1);
insert into SUB(UID,LID) values (2,2);
insert into SUB(UID,LID) values (2,4);
insert into SUB(UID,LID) values (3,3);
insert into SUB(UID,LID) values (3,4);
insert into SUB(UID,LID) values (4,2);
insert into SUB(UID,LID) values (5,1);
insert into SUB(UID,LID) values (5,2);
insert into SUB(UID,LID) values (5,3);
insert into SUB(UID,LID) values (5,4);

insert into THUMB(UID,BID) values(1,2);
insert into THUMB(UID,BID) values(1,3);
insert into THUMB(UID,BID) values(1,4);
insert into THUMB(UID,BID) values(1,7);
insert into THUMB(UID,BID) values(2,1);
insert into THUMB(UID,BID) values(2,4);
insert into THUMB(UID,BID) values(2,7);
insert into THUMB(UID,BID) values(3,4);
insert into THUMB(UID,BID) values(3,7);
insert into THUMB(UID,BID) values(4,2);
insert into THUMB(UID,BID) values(4,7);
insert into THUMB(UID,BID) values(5,2);
insert into THUMB(UID,BID) values(5,3);
insert into THUMB(UID,BID) values(5,4);
insert into THUMB(UID,BID) values(5,7);
insert into THUMB(UID,BID) values(6,7);
insert into THUMB(UID,BID) values(7,6);

insert into TOPDAY(TYEAR,TMONTH,TDAY,BID,TNO) values (2019,4,20,1,1);
insert into TOPDAY(TYEAR,TMONTH,TDAY,BID,TNO) values (2019,4,20,2,2); 
insert into TOPDAY(TYEAR,TMONTH,TDAY,BID,TNO) values (2019,4,27,3,1); 
insert into TOPDAY(TYEAR,TMONTH,TDAY,BID,TNO) values (2019,4,28,4,1);
insert into TOPDAY(TYEAR,TMONTH,TDAY,BID,TNO) values (2019,4,29,7,1); 
insert into TOPDAY(TYEAR,TMONTH,TDAY,BID,TNO) values (2019,4,29,6,2); 