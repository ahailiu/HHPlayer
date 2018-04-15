package com.tencent.mediaplayer;

import android.content.Context;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

/**
 * Created by ahailiu-MC1 on 2018/3/30.
 */

public class PlayerView extends SurfaceView {
    public PlayerView(Context context) {
        super(context);
    }

    public void addCallback(SurfaceHolder.Callback sc) {
        getHolder().addCallback(sc);
    }

    public void removeCallback(SurfaceHolder.Callback sc) {
        getHolder().removeCallback(sc);
    }
}
