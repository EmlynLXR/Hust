use DBexp;
Go
/**增删改*/

--可正确删除/修改MBLOG
insert into MBLOG(BID,TITLE,UID,PYEAR,PMONTH,PDAY,CONT) values (8,null,1,2019,4,22,'人过的日子必是一日遇佛，一日遇魔。——贾平凹 《老生》');
delete from MBLOG where BID = 2;
update MBLOG set BID=8 where BID=1;

--可禁止
insert into THUMB(UID,BID) values(1,1);	
update THUMB set BID=1 where UID=1 and BID=3;

--可正确删除
delete from USERS where UID = 2;

--删除B_L，但不清楚微博
delete from LABEL where LID=4;

--可判断插入错误
insert into THUMB(UID,BID)values(1,9);


DROP TABLE IF EXISTS FANS_3;
select * into FANS_3 from USERS where UID in(select UID from FOLLOW where FOLLOW.UIDFLED=3);

insert into FANS_3(UID,NAME,SEX,BYEAR,CITY) values (1,'王一','男',2001,'武汉');






