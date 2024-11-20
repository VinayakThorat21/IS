import javax.crypto.Mac;
import javax.crypto.spec.SecretKeySpec;
import java.util.Base64;

public class HMAC {

    // Method to generate HMAC using a specified algorithm
    public static String generateHMAC(String message, String secretKey, String algorithm) throws Exception {
        // Create a secret key specification based on the input key and algorithm
        SecretKeySpec keySpec = new SecretKeySpec(secretKey.getBytes(), algorithm);

        // Initialize the Mac instance with the specified algorithm
        Mac mac = Mac.getInstance(algorithm);
        mac.init(keySpec);

        // Compute the HMAC and encode the result in Base64
        byte[] hmacBytes = mac.doFinal(message.getBytes());
        return Base64.getEncoder().encodeToString(hmacBytes);
    }

    public static void main(String[] args) {
        try {
            String message = "This is a secure message.";   // Message to be authenticated
            String secretKey = "vinayak";                   // Secret key for HMAC
            String algorithm = "HmacSHA256";                // HMAC algorithm (e.g., HmacSHA256)

            // Generate HMAC
            String hmac = generateHMAC(message, secretKey, algorithm);

            // Print the result
            System.out.println("Message: " + message);
            System.out.println("Secret Key: " + secretKey);
            System.out.println("HMAC (" + algorithm + "): " + hmac);

        } catch (Exception e) {
            System.err.println("Error generating HMAC: " + e.getMessage());
        }
    }
}
