import subprocess, textwrap


def test_burst_stops_previous_animation():
    js = textwrap.dedent('''
    let frames=0;
    function requestAnimationFrame(fn){ return setTimeout(()=>{ frames++; fn(performance.now()); }, 16); }
    function cancelAnimationFrame(id){ clearTimeout(id); }
    let particles=[]; let anim=null; let dpr=1; let burstId=0;
    function burst(){
      cancelAnimationFrame(anim); particles=[]; const id=++burstId;
      particles.push({t:0,life:50});
      const start=performance.now(); let last=start;
      (function loop(now){ if(id!==burstId) return; const dt=now-last; last=now; let alive=false;
        for(const p of particles){ p.t+=dt; if(p.t>p.life) continue; alive=true; }
        if(alive){ anim=requestAnimationFrame(loop); }
      })(start);
    }
    for(let i=0;i<6;i++){ burst(); }
    setTimeout(()=>{ console.log(frames); }, 100);
    ''')
    out = subprocess.check_output(['node','-e', js], text=True).strip()
    assert int(out) < 10
