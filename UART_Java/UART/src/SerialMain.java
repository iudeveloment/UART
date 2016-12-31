public class SerialMain {
	public static final String PORT = "COM5";
	
	public static void main(String[] args) {
		try {
			new Serial().connect(PORT);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
