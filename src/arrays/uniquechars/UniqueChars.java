


public class UniqueChars
{

	public static Boolean isUniqueChars(String mystring)
	{
		boolean bit[];
		try{
			for (byte mychar : mystring.getBytes("US-ASCII"))
			{
				System.out.println(mychar);

			}
		} 
		catch(java.lang.Exception a)
		{

			
		}
		return false;
	}

 	public static void main(String[] args)
 	{
 		if (args.length>0)
 		{
 			System.out.println(isUniqueChars(args[0]));

 		}
 		/*
    	for(String arg : args)
    	{
    		System.out.println(String.format("MyArg %s", arg));
    	}
    	*/
  	}
}