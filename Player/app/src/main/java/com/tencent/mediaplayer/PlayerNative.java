package com.tencent.mediaplayer;

import android.media.MediaCodecInfo;
import android.media.MediaCodecList;
import android.view.Surface;

/**
 * Created by ahailiu-MC1 on 2018/3/28.
 */

public class PlayerNative {
    static {
        System.loadLibrary("PlayerCore");
    }

    private static String MediaCodec_GetCodecName(String mimeType) {
        for (int i=0; i<MediaCodecList.getCodecCount(); i++) {
            MediaCodecInfo info = MediaCodecList.getCodecInfoAt(i);
            if (info.isEncoder()) {
                continue;
            }

            String[] types = info.getSupportedTypes();
            for (int j=0; j<types.length; j++) {
                String type = types[j];
                if (type.equalsIgnoreCase(mimeType)) {
                    return info.getName();
                }
            }
        }

        return null;
    }

    public native int NativePlayer_PlayerOpen(Surface surface);

}
