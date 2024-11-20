import java.security.*;
import javax.crypto.Cipher;
import java.util.Base64;

public class KeyRole {

    // Encrypt a message using the public key
    public static String encryptMessage(PublicKey publicKey, String message) throws Exception {
        Cipher cipher = Cipher.getInstance("RSA");
        cipher.init(Cipher.ENCRYPT_MODE, publicKey);
        byte[] encryptedBytes = cipher.doFinal(message.getBytes());
        return Base64.getEncoder().encodeToString(encryptedBytes);
    }

    // Decrypt a message using the private key
    public static String decryptMessage(PrivateKey privateKey, String encryptedMessage) throws Exception {
        Cipher cipher = Cipher.getInstance("RSA");
        cipher.init(Cipher.DECRYPT_MODE, privateKey);
        byte[] decryptedBytes = cipher.doFinal(Base64.getDecoder().decode(encryptedMessage));
        return new String(decryptedBytes);
    }

    // Sign a message using the private key
    public static String signMessage(PrivateKey privateKey, String message) throws Exception {
        Signature signature = Signature.getInstance("SHA256withRSA");
        signature.initSign(privateKey);
        signature.update(message.getBytes());
        byte[] signedBytes = signature.sign();
        return Base64.getEncoder().encodeToString(signedBytes);
    }

    // Verify a signature using the public key
    public static boolean verifySignature(PublicKey publicKey, String message, String signatureStr) throws Exception {
        Signature signature = Signature.getInstance("SHA256withRSA");
        signature.initVerify(publicKey);
        signature.update(message.getBytes());
        byte[] signatureBytes = Base64.getDecoder().decode(signatureStr);
        return signature.verify(signatureBytes);
    }

    // Generate RSA key pair (private and public keys)
    public static KeyPair generateKeyPair() throws Exception {
        KeyPairGenerator keyPairGen = KeyPairGenerator.getInstance("RSA");
        keyPairGen.initialize(2048); // Set key size to 2048 bits
        return keyPairGen.generateKeyPair();
    }

    public static void main(String[] args) throws Exception {
        // Generate a pair of keys
        KeyPair keyPair = generateKeyPair();
        PrivateKey privateKey = keyPair.getPrivate();
        PublicKey publicKey = keyPair.getPublic();

        String message = "This is a secure message."; // Sample message

        // Encrypt and decrypt the message
        String encryptedMessage = encryptMessage(publicKey, message);
        String decryptedMessage = decryptMessage(privateKey, encryptedMessage);

        // Sign and verify the message
        String signature = signMessage(privateKey, message);
        boolean isVerified = verifySignature(publicKey, message, signature);

        // Print results
        System.out.println("Encrypted Message: " + encryptedMessage);
        System.out.println("Decrypted Message: " + decryptedMessage);
        System.out.println("Signature: " + signature);
        System.out.println("Signature Verified: " + isVerified);
    }
}
