import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class SHA {

    // Generate SHA-256 hash for a given input
    public static String hash(String data, String variant) throws NoSuchAlgorithmException {
        MessageDigest digest = MessageDigest.getInstance("SHA-" + variant);
        byte[] hashBytes = digest.digest(data.getBytes());
        return bytesToHex(hashBytes);
    }

    // Convert bytes to hexadecimal format
    private static String bytesToHex(byte[] bytes) {
        StringBuilder hexString = new StringBuilder();
        for (byte b : bytes) {
            String hex = Integer.toHexString(0xff & b);
            if (hex.length() == 1) hexString.append('0');
            hexString.append(hex);
        }
        return hexString.toString();
    }

    public static void main(String[] args) {
        try {
            String data = "Hello there, Vinayak 5102 on line!";
            System.out.println("Original Data: " + data);

            // Generate SHA-256 hash
            String hash = hash(data, "256"), expected = "4bda5cf8f661a40513f2cc4f56763681258d88d0d3b93aaaad8b9f2fba3b8223";
            if(hash.equals(expected)) System.out.println("SHA-256 Hash: " + hash);

        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
    }
}
