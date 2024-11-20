package archives;
import java.security.*;
import java.util.Base64;

public class Test {
    // Key pair generation
    public static KeyPair genKeys() throws Exception {
        KeyPairGenerator keyGen = KeyPairGenerator.getInstance("DSA");
        keyGen.initialize(1024);
        return keyGen.generateKeyPair();
    }

    // Sign the message
    public static String signMsg(String msg, PrivateKey key) throws Exception {
        Signature sign = Signature.getInstance("SHA256withDSA");
        sign.initSign(key);
        sign.update(msg.getBytes());
        byte[] signBytes = sign.sign();
        return Base64.getEncoder().encodeToString(signBytes);
    }

    // Verify signature
    public static boolean verifySign(String msg, String msgSign, PublicKey key) throws Exception {
        Signature sign = Signature.getInstance("SHA256withDSA");
        sign.initVerify(key);
        sign.update(msg.getBytes());
        byte[] signBytes = Base64.getDecoder().decode(msgSign);
        return sign.verify(signBytes);
    }

    // Driver code
    public static void main(String ... args) throws Exception {
        String msg = "Hello from Vinayak!", sign;
        KeyPair keys = genKeys();

        sign = signMsg(msg, keys.getPrivate());
        System.out.println("Sign: " + sign);

        if(verifySign(msg, sign, keys.getPublic())) {
            System.out.println("Signature is authentic.");
        }
    }
}