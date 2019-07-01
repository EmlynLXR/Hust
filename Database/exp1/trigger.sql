use DBexp;
Go

--更新点赞表
go
drop trigger if exists insert_THUMB;
go
create trigger insert_THUMB on THUMB
AFTER insert,update
as
begin
	DECLARE @newUID INT
	DECLARE @newBID INT
	SELECT @newUID=UID FROM inserted
	SELECT @newBID=BID FROM inserted
		IF @newUID=(SELECT UID FROM MBLOG WHERE BID=@newBID)
			BEGIN
				RAISERROR('禁止博文作者给自己点赞，操作被禁止',1,1)
				rollback transaction
			END
END


--更新用户表
go
drop trigger if exists delete_USER;
go
create trigger delete_USER on USERS
INSTEAD OF delete
as
begin
	DECLARE @id INT
	select @id=UID from deleted
	delete from MBLOG where UID=@id
	delete from FOLLOW where UID=@id or UIDFLED=@id
	delete from FRIENDS where UID=@id or FUID=@id
	delete from USERS where UID=@id
END



