
import java.util.ArrayList;	
import java.lang.Thread;

class bencharray {


	
public static void main (String []args) {
	
	// code
	long start = System.nanoTime();
	ArrayList arrayList = new ArrayList();
	//arrayList.ensureCapacity();
	
	
	
	for (int i=0; i<10000000; i++) {
		arrayList.add(i);
	}
	String s = String.format("%f s\n", (System.nanoTime() - start) / 1000000000f);
	System.out.println(s);
	
	try {
		Thread.sleep(5000);
	} catch (Exception e) {
		
	}
	
	
}




}

