# stm32_LL_spi_st7735s
Use ST LL library and  DMA to drive SPI screen st7735s

## Pinmap
![connect](/img/pinout.png)

## Use Arm-2D
The warehouse has been adapted to the drawing function `Disp0_DrawBitmap()` required by Arm-2d. 
```
static  IMPL_PFB_ON_LOW_LV_RENDERIN(__pfb_render_handler)
{
    const arm_2d_tile_t *ptTile = &(ptPFB->tTile);

    ARM_2D_UNUSED(pTarget);
    ARM_2D_UNUSED(bIsNewFrame);

    Disp0_DrawBitmap(ptTile->tRegion.tLocation.iX,
                    ptTile->tRegion.tLocation.iY,
                    ptTile->tRegion.tSize.iWidth,
                    ptTile->tRegion.tSize.iHeight,
                    ptTile->pchBuffer);

    arm_2d_helper_pfb_report_rendering_complete(&s_tPFBHelper, 
                                                (arm_2d_pfb_t *)ptPFB);
}
```

## TODO
DMA