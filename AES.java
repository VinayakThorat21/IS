import javax.crypto.Cipher;
import javax.crypto.KeyGenerator;
import javax.crypto.SecretKey;
import java.security.SecureRandom;
import java.util.Base64;
import javax.crypto.spec.IvParameterSpec;

public class AES {

    // Generate AES key
    public static SecretKey generateKey() throws Exception {
        KeyGenerator keyGen = KeyGenerator.getInstance("AES");
        keyGen.init(128); // AES supports 128, 192, and 256-bit key sizes
        return keyGen.generateKey();
    }

    // Encrypt data using AES
    public static String encrypt(String data, SecretKey key) throws Exception {
        Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
        SecureRandom random = new SecureRandom();
        byte[] iv = new byte[16]; // AES block size (128 bits = 16 bytes)
        random.nextBytes(iv); // Generate random IV

        // Initialize cipher for encryption with key and IV
        cipher.init(Cipher.ENCRYPT_MODE, key, new IvParameterSpec(iv));
        byte[] encryptedBytes = cipher.doFinal(data.getBytes());

        // Combine IV and encrypted bytes, then encode to Base64 for easy display
        byte[] ivAndEncrypted = new byte[iv.length + encryptedBytes.length];
        System.arraycopy(iv, 0, ivAndEncrypted, 0, iv.length);
        System.arraycopy(encryptedBytes, 0, ivAndEncrypted, iv.length, encryptedBytes.length);

        return Base64.getEncoder().encodeToString(ivAndEncrypted); // Returning Base64 encoded string
    }

    // Decrypt data using AES
    public static String decrypt(String encryptedData, SecretKey key) throws Exception {
        byte[] ivAndEncrypted = Base64.getDecoder().decode(encryptedData);

        byte[] iv = new byte[16];
        byte[] encryptedBytes = new byte[ivAndEncrypted.length - iv.length];

        // Extract IV and encrypted bytes
        System.arraycopy(ivAndEncrypted, 0, iv, 0, iv.length);
        System.arraycopy(ivAndEncrypted, iv.length, encryptedBytes, 0, encryptedBytes.length);

        Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");

        // Initialize cipher for decryption with key and IV
        cipher.init(Cipher.DECRYPT_MODE, key, new IvParameterSpec(iv));
        byte[] decryptedBytes = cipher.doFinal(encryptedBytes);

        return new String(decryptedBytes);
    }

    public static void main(String[] args) {
        try {
            String data = "Hello, AES Encryption!";
            System.out.println("Original Data: " + data);

            // Generate AES key
            SecretKey key = generateKey();

            // Encrypt the data
            String encryptedData = encrypt(data, key);
            System.out.println("Encrypted Data: " + encryptedData);

            // Decrypt the data
            String decryptedData = decrypt(encryptedData, key);
            System.out.println("Decrypted Data: " + decryptedData);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
