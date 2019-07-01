use DBexp;
Go
--自定义函数
drop function if exists uid_topday
Go
create function uid_topday(@inputuid int) returns int as
begin
	declare @CountDay int
	select @CountDay = count(TOPDAY.BID)from MBLOG,TOPDAY
										where MBLOG.UID=@inputuid and MBLOG.BID=TOPDAY.BID
										group by MBLOG.UID
	return @CountDay
end
Go
select USERS.UID,dbo.uid_topday(USERS.UID)
from USERS
where USERS.BYEAR>2000 and dbo.uid_topday(USERS.UID)>=1;

--存储过程
drop procedure if exists Top_thumb_update
Go
create procedure Top_thumb_update as
begin 
	DROP TABLE if exists TOP_THUMB
	select top 100 THUMB.BID,count(THUMB.UID) as CountThumb into TOP_THUMB from THUMB group by THUMB.BID order by count(THUMB.UID) desc
end
Go
exec dbo.Top_thumb_update;
select * from TOP_THUMB
--事务验证
begin transaction
update USERS set NAME = '1' where UID=1;
update USERS set uid = 1 where UID=2;
if @@ERROR>0
	begin rollback transaction end
else 
	begin commit transaction end
