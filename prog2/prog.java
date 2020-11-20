public class Point {
   int x;
   int y;
}

public void reflect(Point p) {
   int temp = p.x;
   int temp2 = p.y;
   p.x = temp2;
   p.y = temp;
}

public static void main(String[] args) {
   Point one = new Point(); // allocation site 0
   one.x = 1; 
   one.y = 6;
   
   Point two = new Point(); // allocation site 1
   two.x = 4; 
   two.y = 7;
   
   Point three = new Point(); // allocation site 2
   three.x = 2;
   three.y = 1;

   reflect(one); // invocation site 0
   reflect(two); // invocation site 1
}
