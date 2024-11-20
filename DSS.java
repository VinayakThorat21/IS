import java.security.*;
import java.util.Base64;

public class DSS {

    // Generate a pair of DSA keys (public and private)
    public static KeyPair generateKeyPair() throws Exception {
        KeyPairGenerator keyGen = KeyPairGenerator.getInstance("DSA");
        keyGen.initialize(2048); // DSA typically uses 1024, 2048, or 3072-bit keys
        return keyGen.generateKeyPair();
    }

    // Sign a message using the private key
    public static String signMessage(String message, PrivateKey privateKey) throws Exception {
        Signature signature = Signature.getInstance("SHA256withDSA");
        signature.initSign(privateKey);
        signature.update(message.getBytes());
        byte[] signedBytes = signature.sign();
        return Base64.getEncoder().encodeToString(signedBytes);
    }

    // Verify the signature using the public key
    public static boolean verifySignature(String message, String signatureStr, PublicKey publicKey) throws Exception {
        Signature signature = Signature.getInstance("SHA256withDSA");
        signature.initVerify(publicKey);
        signature.update(message.getBytes());
        byte[] signedBytes = Base64.getDecoder().decode(signatureStr);
        return signature.verify(signedBytes);
    }

    public static void main(String[] args) {
        try {
            String message = "Hello, DSS digital signature!";
            System.out.println("Message: " + message);

            // Generate key pair
            KeyPair keyPair = generateKeyPair();

            // Sign the message
            String signature = signMessage(message, keyPair.getPrivate());
            System.out.println("Digital Signature: " + signature);

            // Verify the signature
            boolean isVerified = verifySignature(message, signature, keyPair.getPublic());
            System.out.println("Signature Verified: " + isVerified);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
