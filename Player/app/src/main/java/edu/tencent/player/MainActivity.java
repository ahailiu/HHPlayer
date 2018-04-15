package edu.tencent.player;

import android.app.Activity;
import android.app.Application;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.ViewGroup;

import com.tencent.mediaplayer.PlayerNative;
import com.tencent.mediaplayer.PlayerView;

public class MainActivity extends Activity {
    private static final String TAG = "MainActivity";
    private PlayerNative player = new PlayerNative();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        PlayerView sf = new PlayerView(this);

        sf.addCallback(new SurfaceHolder.Callback() {
            @Override
            public void surfaceCreated(SurfaceHolder holder) {
                Log.d(TAG, "surfaceCreated.");

                int ret = player.NativePlayer_PlayerOpen(holder.getSurface());
            }

            @Override
            public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
                Log.d(TAG, "surfaceChanged.");
            }

            @Override
            public void surfaceDestroyed(SurfaceHolder holder) {
                Log.d(TAG, "surfaceDestroyed.");
            }
        });

        ViewGroup videolayout = findViewById(R.id.videolayout);
        ViewGroup.LayoutParams param = new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT,
                ViewGroup.LayoutParams.MATCH_PARENT);

        sf.setLayoutParams(param);
        sf.setVisibility(View.VISIBLE);
        videolayout.addView(sf);
        videolayout.setBackgroundColor(Color.BLACK);

        Log.d(TAG, "onCreate.\n");
    }
}
