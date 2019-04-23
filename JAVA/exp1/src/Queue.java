import java.util.Stack;
import java.util.NoSuchElementException;
public class Queue<E> extends Stack<E>{
    private  Stack<E> stk;
    public final int dump = 5;
    public Queue( ){
        stk = new Stack<E>();
    }
    public boolean add(E e) throws IllegalStateException, ClassCastException, 
NullPointerException, IllegalArgumentException{  
        if(e == null)
            throw new NullPointerException();
        else if(stk.size()<dump)
        {
            stk.push(e);
            return true;
        }
        else if(this.isEmpty())
        {
            while(!stk.empty())
            {
                this.push(stk.pop());
            }
            stk.push(e);
            return true;
        }
        else
            throw new IllegalStateException();
    }

    public boolean offer(E e) throws ClassCastException, NullPointerException, 
IllegalArgumentException{
        if(e == null)
            throw new NullPointerException();
        else if(stk.size()<dump)
        {
            stk.push(e);
            return true;
        }
        else if(this.isEmpty())
        {
            while(!stk.empty())
            {
                this.push(stk.pop());
            }
            stk.push(e);
            return true;
        }
        else
            return false;
    }
    public E remove( ) throws NoSuchElementException {   
        E re = null;
        if(!this.empty())
            re = this.pop();
        else if(!stk.empty())
        {
            while(!stk.empty())
            {
                this.push(stk.pop());
            }
            re = this.pop();
        }
        else
            throw new NoSuchElementException();
        return re;
    }
    public E poll( ) {   
        E re = null;
        if(!this.empty())
            re = this.pop();
        else if(!stk.empty())
        {
            while(!stk.empty())
            {
                re = this.push(stk.pop());
            }
            this.pop();
        }
        else
            re = null;
        return re;    
    }
    public E peek ( ) { 
        if(!this.empty())
            return super.peek();
        else if(!stk.empty())
        {
            return stk.elementAt(0);
        }
        else
            return null;  
    }
    public E element( ) throws NoSuchElementException {  
        if(!this.empty())
            return this.peek();
        else if(!stk.empty())
        {
            return stk.elementAt(0);
        }
        else
            throw new NoSuchElementException();   
    }
    public boolean show(){
        System.out.println("---this---");
        for(E x : this){
            System.out.println(x);
        }
        System.out.println("---stk---");
        for(E x : stk){
            System.out.println(x);
        }
        return true;
    }
}
