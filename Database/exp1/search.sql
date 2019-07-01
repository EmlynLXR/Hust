use DBexp;
Go
--1查询“张三”用户关注的所有用户的ID号、姓名、性别、出生年份，所在城市，并且按照出生年份的降序排列，同一个年份的则按照用户ID号升序排列。
select USERS2.UID,USERS2.NAME,USERS2.SEX,USERS2.BYEAR,USERS2.CITY
from FOLLOW,USERS USERS1,USERS USERS2
where USERS1.NAME='张三' and USERS1.UID=FOLLOW.UID and FOLLOW.UIDFLED=USERS2.UID
order by USERS2.BYEAR desc,USERS2.UID asc;


--2查找没有被任何人点赞的博文ID、标题以及发表者姓名，并将结果按照标题字符顺序排列。
select MBLOG.TITLE,MBLOG.TITLE,USERS.NAME
from MBLOG,USERS
where MBLOG.UID=USERS.UID and MBLOG.BID not in(
select MBLOG.BID
from THUMB
where THUMB.BID=MBLOG.BID
);


--3查找2000年以后出生的武汉市用户发表的进入过头条的博文ID；
select TOPDAY.BID
from TOPDAY,MBLOG,USERS
where TOPDAY.BID=MBLOG.BID and MBLOG.UID=USERS.UID and USERS.BYEAR>=2000 and USERS.CITY='武汉';


--4查找订阅了所有分类的用户ID；
select USERS.UID,count(SUB.LID)
from USERS,SUB
where USERS.UID=SUB.UID
group by USERS.UID
having count(SUB.LID) = (select count(*)from LABEL); 


--5查找出生年份小于1970年或者大于2010年的用户ID、出生年份、所在城市，要求where子句中只能有一个条件表达式；
select USERS.UID,USERS.BYEAR,USERS.CITY
from USERS
where USERS.BYEAR not between 1970 and 2010;


--6统计每个城市的用户数；
select USERS.CITY,count (USERS.UID)
from USERS
group by USERS.CITY;


--7统计每个城市的每个出生年份的用户数，并将结果按照城市的升序排列，同一个城市按照出生用户数的降序排列其相应的年份；
select USERS.CITY,USERS.BYEAR,count (USERS.UID)
from USERS
group by USERS.CITY,USERS.BYEAR
order by USERS.CITY asc,USERS.BYEAR desc;


--8查找被点赞数超过10的博文ID号；
select THUMB.BID,count(THUMB.UID)
from THUMB
group by THUMB.BID
having count(THUMB.UID)>10;


--9查找被2000年后出生的用户点赞数超过10的博文ID号；
select THUMB.BID,count(THUMB.UID)
from THUMB,USERS
where THUMB.UID = USERS.UID and USERS.BYEAR >2000
group by THUMB.BID
having count(THUMB.UID)>10;


--10查找被2000年后出生的用户点赞数超过10的每篇博文的进入头条的次数；
select TOPDAY.BID,count(TOPDAY.TNO)
from TOPDAY
where TOPDAY.BID IN (
	select THUMB.BID
	from THUMB,USERS
	where THUMB.UID = USERS.UID and USERS.BYEAR >2000
	group by THUMB.BID
	having count(THUMB.UID)>10)
	group by TOPDAY.BID;


--11查找订阅了文学、艺术、哲学、音乐中至少一种分类的用户ID，要求不能使用嵌套查询，且where子句中最多只能包含两个条件；
select DISTINCT SUB.UID
from SUB,LABEL
where SUB.LID=LABEL.LID and LABEL.LNAME in ('文学','艺术','哲学','音乐');


--12查找标题中包含了“最多地铁站”和“_华中科技大学”两个词的博文基本信息；
select *
from MBLOG
where MBLOG.TITLE like '%最多地铁站%' or MBLOG.TITLE like '%华中科技大学%';


--13 查找所有相互关注的用户对的两个ID号，要求不能使用嵌套查询；
--考虑1 2 和2 1是否能去重
select a.UID,b.UID
from FOLLOW a,FOLLOW b
where a.UIDFLED=b.UID and a.UID=b.UIDFLED and a.UID>b.UID;


--14查找好友圈包含了5号用户好友圈的用户ID；
select distinct f1.UID
from FRIENDS f1
where not exists (
	select * 
	from FRIENDS f2 
	where f2.UID=5 and f2.FUID not in(
		select FUID 
		from FRIENDS f3
		where f3.UID=f1.UID
	)
);     

--15查找2019年4月20日每一篇头条博文的ID号、标题以及该博文的每一个分类ID，要求即使该博文没有任何分类ID也要输出其ID号、标题；
select TOPDAY.BID,MBLOG.TITLE,B_L.LID
from TOPDAY,MBLOG,B_L
where TOPDAY.TYEAR=2019 and TOPDAY.TMONTH=4 and TOPDAY.TDAY=20 and TOPDAY.BID=MBLOG.BID and TOPDAY.BID=B_L.BID;


--16查找至少有3名共同好友的所有用户对的两个ID号。
--考虑1 2 和2 1是否能去重
select a.UID,b.UID,count(b.FUID)
from FRIENDS a,FRIENDS b
where a.UID!=b.UID and a.FUID=b.FUID and a.UID>b.UID
group by a.UID,b.UID
having count(b.FUID)>=2;


--17创建视图：查阅DBMS内部函数，创建一个显示当日热度排名前十的微博信息的视图，其中的属性包括：博文ID、博文标题、发表者ID、发表者姓名、被点赞数。
DROP VIEW  if exists MBLOG_VIEW;
go
create view MBLOG_VIEW(BID,TITLE,UID,NAME,CountNUM) as(
select MBLOG.BID,MBLOG.TITLE,MBLOG.UID,USERS.NAME,count(THUMB.UID)
from THUMB,MBLOG,USERS,TOPDAY
where TOPDAY.BID = MBLOG.BID and MBLOG.BID=THUMB.BID and MBLOG.UID=USERS.UID and TOPDAY.TNO<10 and TOPDAY.TYEAR = (select YEAR(GETDATE())) and TOPDAY.TMONTH = (select MONTH(GETDATE())) and TOPDAY.TDAY = (select DAY(GETDATE()))
group by MBLOG.BID,MBLOG.TITLE,MBLOG.UID,USERS.NAME
);
Go
select * from MBLOG_VIEW;
