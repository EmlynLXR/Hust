use DBexp
go

drop table if exists test
create table test(ID INT,PRICE INT);

insert into test (ID,PRICE)values(1,10),(2,20),(3,30)


BEGIN TRAN
	UPDATE test SET PRICE += 1 WHERE ID = 2
	COMMIT TRAN



rollback tran

DBCC OPENTRAN
