use DBexp;
--删除逻辑设备
EXEC sp_dropdevice backup_DBexp

--新建逻辑设备
EXEC sp_addumpdevice 'DISK','backup_DBexp','D:\Microsoft SQL Server\MSSQL14.MSSQLSERVER\BACKUPDEV\dbexp.bak'

--备份数据库
BACKUP DATABASE DBexp TO backup_DBexp

--备份日志文件
BACKUP LOG DBexp TO backup_DBexp

--删除数据库
use master   
go      
declare @dbname sysname   
set @dbname = 'DBexp' --这个是要删除的数据库库名   
      
declare @s nvarchar(1000)   
declare tb cursor local  
for 
    select s = 'kill   ' + cast(spid as varchar) 
    from   master.dbo.sysprocesses 
    where  dbid = DB_ID(@dbname)   
      
open   tb     
fetch   next   from   tb   into   @s   
while @@fetch_status = 0 
begin 
    exec (@s)  
    fetch next from tb into @s 
end   
close   tb   
deallocate   tb 
DROP DATABASE DBexp;

--还原数据库
RESTORE DATABASE DBexp FROM backup_DBexp;


--SQL Server 阻止了对组件“xp_cmdshell”的 过程“sys.xp_cmdshell”的访问，因为此组件已作为此服务器安全配置的一部分而被关闭。
go
sp_configure 'show advanced options',1
reconfigure
go
sp_configure 'xp_cmdshell',1
reconfigure



--导出到excel
--EXEC master..xp_cmdshell 'bcp "SELECT * FROM DBexp.USERS"  queryout  “D:\Microsoft SQL Server\MSSQL14.MSSQLSERVER\BACKUPDEV\USERS.txt” -c'