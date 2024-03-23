package com.iuantu.library1;

public class NativeLib {

    // Used to load the 'library1' library on application startup.
    static {
        System.loadLibrary("library1");
    }

    /**
     * A native method that is implemented by the 'library1' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}