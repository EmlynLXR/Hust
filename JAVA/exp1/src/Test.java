import java.util.NoSuchElementException;
import java.util.Scanner;
public class Test {
    public static void main(String[]args)throws IllegalStateException, ClassCastException,
            NullPointerException, IllegalArgumentException{
        Queue<Integer>queue = new Queue<Integer>();
        Scanner scanner = new Scanner(System.in);
        int op;
        Integer para,ret;
        boolean exit = true;
        while(exit)
        {
            System.out.println("0 exit\n1 add\t2 offer\n3 remove\t4 poll\n5 peek\t6 element\t7 show\ninput:");
            op = scanner.nextInt();
            switch(op)
            {
                case 0:
                    exit = false;
                    break;
                case 1:
                    try {
                        while (!scanner.hasNext("#")) {
                            para = scanner.nextInt();
                            queue.add(para);
                        }
                    }
                    catch(IllegalStateException|NoSuchElementException ae) {
                        System.out.println(ae);
                    }
                    scanner.next();
                    break;
                case 2:
                    try{
                        while (!scanner.hasNext("#")) {
                            para = scanner.nextInt();
                            if(queue.offer(para))
                            {
                                System.out.println("添加成功");
                            }
                            else
                            {
                                System.out.println("添加失败");
                            }
                        }
                    }
                    catch (NoSuchElementException e) {
                        System.out.println(e);
                    }
                    scanner.next();
                    break;
                case 3:
                    try{
                        ret = queue.remove();
                        System.out.println("ret = "+ret);
                    }
                    catch (NoSuchElementException e)
                    {
                        System.out.println(e);
                    }
                    break;
                case 4:
                    ret = queue.poll();
                    if(ret != null)
                        System.out.println("ret = "+ret);
                    else
                        System.out.println("Queue is empty.\n");
                    break;
                case 5:
                    ret = queue.peek();
                    if(ret != null)
                        System.out.println("ret = "+ret);
                    else
                        System.out.println("Queue is empty.\n");
                    break;
                case 6:
                    try{
                        ret = queue.element();
                        System.out.println("ret = "+ret);
                    }
                    catch (NoSuchElementException e)
                    {
                        System.out.println(e);
                    }
                    break;
                case 7:
                    queue.show();
                    break;
                default:
                    break;
            }
        }
        scanner.close();
    }
}
